/*
 * c-hacker.h
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#ifndef INCLUDE_C_HACKER_H_
#define INCLUDE_C_HACKER_H_

#include "c-hacker-set-mode.h"
#include <setjmp.h>

#if (C_HACKER_MODE == C_HACKER_MODE_STATIC) || (C_HACKER_MODE == C_HACKER_MODE_STATIC_INLINE)
#include <stdint-gcc.h>
#include <stdio.h>
#include <stdlib.h>
#endif

CH_VAR(volatile const char *fail_file_name);
CH_VAR(volatile const char *fail_val_str);
CH_VAR(volatile const char *fail_msg);
CH_VAR(jmp_buf state);

#define _CH_EPS const char *CH_PN(msg), const char *CH_PN(file_name), int CH_PN(line_num), const char *CH_PN(value_str)
#define _CH_CEPS(msg, value_str) msg, __FILE__, __LINE__, value_str

CH_PREFIX ch_fail CH_PARAMS((_CH_EPS))
CH_IMPL (
		if (!state) {
			fprintf(stderr, "[C-Hacker]: fail, but state is NULL!\n"
					"[C-Hacker]: %s:%d > %s\n"
					"[C-Hacker]: message=%s\n"
					"", file_name, line_num, value_str, msg);
			fflush(NULL);
			abort();
		} else {
			fail_file_name = file_name;
			fail_val_str = value_str;
			longjmp(state, line_num);
		}
)

#define _CH_DEC_FUNCS(name, impl_info) \
		CH_PREFIX assert_##name##_c \
			CH_PARAMS((_CH_PARAM_START(char) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(char, impl_info)) \
		CH_PREFIX assert_##name##_s \
			CH_PARAMS((_CH_PARAM_START(short) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(short, impl_info)) \
		CH_PREFIX assert_##name##_i \
			CH_PARAMS((_CH_PARAM_START(int) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int, impl_info)) \
		CH_PREFIX assert_##name##_l \
			CH_PARAMS((_CH_PARAM_START(long) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(long, impl_info)) \
		CH_PREFIX assert_##name##_ll \
			CH_PARAMS((_CH_PARAM_START(long long) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(long long, impl_info)) \
		CH_PREFIX assert_##name##_f \
			CH_PARAMS((_CH_PARAM_START(float) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(float, impl_info)) \
		CH_PREFIX assert_##name##_d \
			CH_PARAMS((_CH_PARAM_START(double) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(double, impl_info)) \
		CH_PREFIX assert_##name##_ld \
			CH_PARAMS((_CH_PARAM_START(long double) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(long double, impl_info)) \
		CH_PREFIX assert_##name##_p \
			CH_PARAMS((_CH_PARAM_START(void *) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(void *, impl_info)) \
		CH_PREFIX assert_##name##_i8 \
			CH_PARAMS((_CH_PARAM_START(int8_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int8_t, impl_info)) \
		CH_PREFIX assert_##name##_i16 \
			CH_PARAMS((_CH_PARAM_START(int16_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int16_t, impl_info)) \
		CH_PREFIX assert_##name##_i32 \
			CH_PARAMS((_CH_PARAM_START(int32_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int32_t, impl_info)) \
		CH_PREFIX assert_##name##_i64 \
			CH_PARAMS((_CH_PARAM_START(int64_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int64_t, impl_info)) \

#define _CH_PARAM_START(type) type CH_PN(a), type CH_PN(b),
#define _CH_DEF_IMPL(type, op) if (a op b) { CH_ERROR(msg,file_name,line_num,value_str) }

_CH_DEC_FUNCS(equal, !=)
_CH_DEC_FUNCS(not_equal, ==)
_CH_DEC_FUNCS(greater, <=)
_CH_DEC_FUNCS(greater_equal, <)
_CH_DEC_FUNCS(less_equal, >)
_CH_DEC_FUNCS(less, >=)

#undef _CH_DEF_IMPL
#undef _CH_PARAM_START

#define _CH_PARAM_START(type) type CH_PN(a),
#define _CH_DEF_IMPL(type, op) if (a op ((type) 0)) { CH_ERROR(msg,file_name,line_num,value_str) }

_CH_DEC_FUNCS(zero, !=)
_CH_DEC_FUNCS(not_zero, ==)
_CH_DEC_FUNCS(positive, <=)
_CH_DEC_FUNCS(not_negative, <)
_CH_DEC_FUNCS(not_positive, >)
_CH_DEC_FUNCS(negative, >=)

#undef _CH_DEF_IMPL
#undef _CH_PARAM_START

#undef _CH_DEC_FUNCS

#define fail(msg) ch_fail(_CH_CEPS(msg, "fail(" #msg ")"))

#define assert_equal(a, b, msg) \
	_Generic((a), \
		long double: assert_equal_ld((a), (long double) (b), _CH_CEPS(msg, "assert_equals" #a ", " #b ")")), \
		double: \
		_Generic((b), \
			long double: assert_equal_ld((long double) (a), (b), _CH_CEPS(msg, "assert_equals" #a ", " #b ")")), \
			default: assert_equal_f((a), (double) (b), _CH_CEPS(msg, "assert_equals" #a ", " #b ")")) \
		), \
		float: \
		_Generic((b), \
			long double: assert_equal_ld((long double)(a), (b), _CH_CEPS(msg, "assert_equals" #a ", " #b ")")), \
			double: assert_equal_d((double) (a), (b), _CH_CEPS(msg, "assert_equals" #a ", " #b ")")), \
			default: assert_equal_f(a, (float) (b), _CH_CEPS(msg, "assert_equals" #a ", " #b ")")) \
		) \
	)
// TODO finish this _Generic and to make that more generic so it also can be used for the other asserts

#endif /* INCLUDE_C_HACKER_H_ */
