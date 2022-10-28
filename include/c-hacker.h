/*
 * c-hacker.h
 *
 * this header declares the assert and fail functions of the C-Hacker API
 *
 * all functions/macros are also declared with a m suffix.
 *   - these functions/macros await an additional argument as (const char*) message
 *     at the end of the argument list
 *
 * fail()
 *  - stop the execution of the current check and report failure
 *
 * the following macros will either stop the execution of the current
 * check and report failure or return normally without changing anything.
 *
 * the following macros check what types are used and delegate to the correct function
 * when there are multiple arguments the sum of all arguments is used to check the type
 * valid types are:
 *  char, short, int, long, long long, float, double, long double, int8_t, int16_t, int32_t, int64_t
 *
 *   assert_equal(a, b)
 *     - fails only not if a == b
 *   assert_not_equal(a, b)
 *     - fails only not if a != b
 *   assert_greater(a, b)
 *     - fails only not if a > b
 *   assert_greater_equal(a, b)
 *     - fails only not if a >= b
 *   assert_less_equal(a, b)
 *     - fails only not if a <= b
 *   assert_less(a, b)
 *     - fails only not if a < b
 *
 *   assert_zero(a)
 *     - fails only not if a == 0
 *   assert_not_zero(a)
 *     - fails only not if a != 0
 *   assert_positive(a)
 *     - fails only not if a > 0
 *   assert_not_negative(a)
 *     - fails only not if a >= 0
 *   assert_not_positive(a)
 *     - fails only not if a <= 0
 *   assert_negative(a)
 *     - fails only not if a < 0
 *
 * the following macros can be used to do checks on strings and memory blocks
 *
 *   assert_str_equal(a, b)
 *     - fails only not if strcmp(const char *a, const char *b) returns 0
 *   assert_str_not_equal(a, b)
 *     - fails only not if strcmp(const char *a, const char *b) returns a value != 0
 *
 *   assert_mem_equal(a, b, size)
 *     - fails only not if memcmp(const void *a, const void *b, size_t size) returns 0
 *   assert_mem_not_equal(a, b, size)
 *     - fails only not if memcmp(const void *a, const void *b, size_t size) returns a value != 0
 *
 * this check can be used to call a function which is expected to fail with the C-Hacker API
 *
 *  assert_fail(void (*a)(void))
 *     - fails only not when the call to a fails
 *
 *  assert_fail_in(void (*a)(void), enum c_hacker_fail_code code)
 *     - fails only not when the call to a fails with the specified code as fail argument
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#ifndef INCLUDE_C_HACKER_H_
#define INCLUDE_C_HACKER_H_

#include "c-hacker-set-mode.h"
#include "c-hacker-fails.h"
#include <setjmp.h>

#if (C_HACKER_MODE == C_HACKER_MODE_STATIC) \
		|| (C_HACKER_MODE == C_HACKER_MODE_STATIC_INLINE) \
		|| defined C_HACKER_DO_INCLUDES
#include <stdint-gcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#define _CH_EPS const char *CH_PN(msg), const char *CH_PN(file_name), int CH_PN(line_num), const char *CH_PN(value_str), enum c_hacker_fail_code CH_PN(code)
#define _CH_CEPS(msg, value_str, code) msg, __FILE__, __LINE__, value_str, code

CH_VAR(const char *fail_file_name);
CH_VAR(int fail_line_num);
CH_VAR(const char *fail_val_str);
CH_VAR(const char *fail_msg);
CH_VAR(jmp_buf *state_pntr);

CH_PREFIX ch_fail CH_PARAMS((_CH_EPS))
CH_IMPL (
		if (!state_pntr) {
			fprintf(stderr, "[C-Hacker]: fail, but state is NULL!\n"
					"[C-Hacker]: %s:%d > %s\n"
					"[C-Hacker]: code=%d\n"
					"[C-Hacker]: message=%s\n"
					"", file_name, line_num, value_str, code, msg);
			fflush(NULL);
			abort();
		} else {
			fail_file_name = file_name;
			fail_line_num = line_num;
			fail_val_str = value_str;
			fail_msg = msg;
			longjmp(*state_pntr, code);
		}
)

#define _CH_DEC_FUNCS(name, impl_info) \
		CH_PREFIX ch_ch_assert_##name##_c \
			CH_PARAMS((_CH_PARAM_START(char) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(char, impl_info, chf_##name)) \
		CH_PREFIX ch_ch_assert_##name##_s \
			CH_PARAMS((_CH_PARAM_START(short) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(short, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_i \
			CH_PARAMS((_CH_PARAM_START(int) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_l \
			CH_PARAMS((_CH_PARAM_START(long) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(long, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_ll \
			CH_PARAMS((_CH_PARAM_START(long long) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(long long, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_f \
			CH_PARAMS((_CH_PARAM_START(float) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(float, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_d \
			CH_PARAMS((_CH_PARAM_START(double) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(double, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_ld \
			CH_PARAMS((_CH_PARAM_START(long double) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(long double, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_p \
			CH_PARAMS((_CH_PARAM_START(void *) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(void *, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_i8 \
			CH_PARAMS((_CH_PARAM_START(int8_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int8_t, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_i16 \
			CH_PARAMS((_CH_PARAM_START(int16_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int16_t, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_i32 \
			CH_PARAMS((_CH_PARAM_START(int32_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int32_t, impl_info, chf_##name)) \
		CH_PREFIX ch_assert_##name##_i64 \
			CH_PARAMS((_CH_PARAM_START(int64_t) _CH_EPS)) \
							CH_IMPL(_CH_DEF_IMPL(int64_t, impl_info, chf_##name)) \

#define _CH_ERR(code) CH_ERROR(msg,file_name,line_num,value_str,code)
#define _CH_IMPL_IMPL(cond,code) if (cond) { _CH_ERR(code) }


#define _CH_PARAM_START(type) type CH_PN(a), type CH_PN(b),
#define _CH_DEF_IMPL(type, op, code) _CH_IMPL_IMPL(a op b, code)

_CH_DEC_FUNCS(equal, !=)
_CH_DEC_FUNCS(not_equal, ==)
_CH_DEC_FUNCS(greater, <=)
_CH_DEC_FUNCS(greater_equal, <)
_CH_DEC_FUNCS(less_equal, >)
_CH_DEC_FUNCS(less, >=)

#undef _CH_DEF_IMPL
#undef _CH_PARAM_START

#define _CH_PARAM_START(type) type CH_PN(a),
#define _CH_DEF_IMPL(type, op, code) _CH_IMPL_IMPL(a op ((type) 0), code)

_CH_DEC_FUNCS(zero, !=)
_CH_DEC_FUNCS(not_zero, ==)
_CH_DEC_FUNCS(positive, <=)
_CH_DEC_FUNCS(not_negative, <)
_CH_DEC_FUNCS(not_positive, >)
_CH_DEC_FUNCS(negative, >=)

#undef _CH_DEF_IMPL
#undef _CH_PARAM_START

#undef _CH_DEC_FUNCS

CH_PREFIX ch_assert_str_equal CH_PARAMS((const char *CH_PN(a), const char *CH_PN(b), _CH_EPS))
CH_IMPL(
		_CH_IMPL_IMPL(strcmp(a, b), chf_str_equal)
)

CH_PREFIX ch_assert_str_not_equal CH_PARAMS((const char *CH_PN(a), const char *CH_PN(b), _CH_EPS))
CH_IMPL(
		_CH_IMPL_IMPL(!strcmp(a, b), chf_str_not_equal)
)

CH_PREFIX ch_assert_mem_equal CH_PARAMS((const char *CH_PN(a), const char *CH_PN(b), size_t CH_PN(size), _CH_EPS))
CH_IMPL(
		_CH_IMPL_IMPL(memcmp(a, b, size), chf_mem_equal)
)

CH_PREFIX ch_assert_mem_not_equal CH_PARAMS((const char *CH_PN(a), const char *CH_PN(b), size_t CH_PN(size), _CH_EPS))
CH_IMPL(
		_CH_IMPL_IMPL(!memcmp(a, b, size), chf_mem_not_equal)
)

CH_PREFIX ch_assert_fail CH_PARAMS((void (*const CH_PN(a))(void), size_t CH_PN(size), _CH_EPS))
CH_IMPL(
/*	 */jmp_buf *old_state = state_pntr;
/*	 */jmp_buf my_buf;
/*	 */state_pntr = &my_buf;
/*	 */int cond = setjmp(my_buf);
/*	 */if (cond) {
	/*	*/state_pntr = old_state;
	/*	*/return;/*
	 */}
/*	 */a();
/*	 */state_pntr = old_state;
/*	 */_CH_ERR(chf_fail)
)

CH_PREFIX ch_assert_fail_with CH_PARAMS((void (*const CH_PN(a))(void), const enum c_hacker_fail_code CH_PN(b), size_t CH_PN(size), _CH_EPS))
CH_IMPL(
/*	 */jmp_buf *old_state = state_pntr;
/*	 */jmp_buf my_buf;
/*	 */state_pntr = &my_buf;
/*	 */int fail_code = setjmp(my_buf);
/*	 */if (fail_code) {
/*	 	  */state_pntr = old_state;
/*	 	  */if (fail_code != b) {
/*	 		  */msg = msg ? msg : "wrong error code!";
/*	 		  */_CH_ERR(chf_fail)
/*	 	  */}
/*	 	  */return;
/*	 */}
/*	 */a();
/*	 */state_pntr = old_state;
/*	 */msg = msg ? msg : "did not fail!";
/*	 */_CH_ERR(chf_fail)
)

#define _CHGen2P(func_name, msg, value_str) \
		_Generic((a + b), \
			long double:        ch_##func_name##_ld ((long double) (a), (long double) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			double:             ch_##func_name##_d  ((     double) (a), (     double) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			float:              ch_##func_name##_f  ((      float) (a), (      float) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			signed long long:   ch_##func_name##_ll ((  long long) (a), (  long long) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			unsigned long long: ch_##func_name##_ll ((  long long) (a), (  long long) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			long:               ch_##func_name##_l  ((       long) (a), (       long) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			int:                ch_##func_name##_i  ((        int) (a), (        int) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			signed short:       ch_##func_name##_s  ((      short) (a), (      short) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			unsigned short:     ch_##func_name##_s  ((      short) (a), (      short) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			signed char:        ch_##func_name##_c  ((       char) (a), (       char) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			unsigned char:      ch_##func_name##_c  ((       char) (a), (       char) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			default:            ch_##func_name##_p  ((      void*) (a), (      void*) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			int8_t:             ch_##func_name##_i8 ((     int8_t) (a), (     int8_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			uint8_t:            ch_##func_name##_i8 ((     int8_t) (a), (     int8_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			int16_t:            ch_##func_name##_i16((    int16_t) (a), (    int16_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			uint16_t:           ch_##func_name##_i16((    int16_t) (a), (    int16_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			int32_t:            ch_##func_name##_i32((    int32_t) (a), (    int32_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			uint32_t:           ch_##func_name##_i32((    int32_t) (a), (    int32_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			int16_t:            ch_##func_name##_i64((    int64_t) (a), (    int64_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
			uint16_t:           ch_##func_name##_i64((    int64_t) (a), (    int64_t) (b), _CH_CEPS(msg, #func_name value_str), chf_##func_name), \
		)

#define _CHGen1P(func_name, msg, value_str) \
		_Generic((a), \
			long double:        ch_##func_name##_ld ((long double) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			double:             ch_##func_name##_d  ((     double) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			float:              ch_##func_name##_f  ((      float) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			signed long long:   ch_##func_name##_ll ((  long long) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			unsigned long long: ch_##func_name##_ll ((  long long) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			long:               ch_##func_name##_l  ((       long) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			int:                ch_##func_name##_i  ((        int) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			signed short:       ch_##func_name##_s  ((      short) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			unsigned short:     ch_##func_name##_s  ((      short) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			signed char:        ch_##func_name##_c  ((       char) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			unsigned char:      ch_##func_name##_c  ((       char) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			default:            ch_##func_name##_p  ((      void*) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			int8_t:             ch_##func_name##_i8 ((     int8_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			uint8_t:            ch_##func_name##_i8 ((     int8_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			int16_t:            ch_##func_name##_i16((    int16_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			uint16_t:           ch_##func_name##_i16((    int16_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			int32_t:            ch_##func_name##_i32((    int32_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			uint32_t:           ch_##func_name##_i32((    int32_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			int16_t:            ch_##func_name##_i64((    int64_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
			uint16_t:           ch_##func_name##_i64((    int64_t) (a), _CH_CEPS(msg, #func_name value_str, chf_##func_name)), \
		)

#define fail() ch_fail(chf_fail_call, _CH_CEPS(NULL, "fail()"))
#define failm(msg) ch_fail(chf_fail_call, _CH_CEPS(msg, "fail(" #msg ")"))

#define assert_equal(a, b)         _CHGen2P(assert_equal        , NULL, "(" #a ", " #b ")")
#define assert_not_equal(a, b)     _CHGen2P(assert_not_equal    , NULL, "(" #a ", " #b ")")
#define assert_greater(a, b)       _CHGen2P(assert_greater      , NULL, "(" #a ", " #b ")")
#define assert_greater_equal(a, b) _CHGen2P(assert_greater_equal, NULL, "(" #a ", " #b ")")
#define assert_less_equal(a, b)    _CHGen2P(assert_less_equal   , NULL, "(" #a ", " #b ")")
#define assert_less(a, b)          _CHGen2P(assert_less         , NULL, "(" #a ", " #b ")")

#define assert_equalm(a, b)         _CHGen2P(assert_equal        , msg, "(" #a ", " #b ")")
#define assert_not_equalm(a, b)     _CHGen2P(assert_not_equal    , msg, "(" #a ", " #b ")")
#define assert_greaterm(a, b)       _CHGen2P(assert_greater      , msg, "(" #a ", " #b ")")
#define assert_greater_equalm(a, b) _CHGen2P(assert_greater_equal, msg, "(" #a ", " #b ")")
#define assert_less_equalm(a, b)    _CHGen2P(assert_less_equal   , msg, "(" #a ", " #b ")")
#define assert_lessm(a, b)          _CHGen2P(assert_less         , msg, "(" #a ", " #b ")")

#define assert_zero(a)         _CHGen1P(assert_zero        , NULL, "(" #a ")")
#define assert_not_zero(a)     _CHGen1P(assert_not_zero    , NULL, "(" #a ")")
#define assert_positive(a)     _CHGen1P(assert_positive    , NULL, "(" #a ")")
#define assert_not_negative(a) _CHGen1P(assert_not_negative, NULL, "(" #a ")")
#define assert_not_positive(a) _CHGen1P(assert_not_positive, NULL, "(" #a ")")
#define assert_negative(a)     _CHGen1P(assert_negative    , NULL, "(" #a ")")

#define assert_zerom(a)         _CHGen1P(assert_zero        , msg, "(" #a ")")
#define assert_not_zerom(a)     _CHGen1P(assert_not_zero    , msg, "(" #a ")")
#define assert_positivem(a)     _CHGen1P(assert_positive    , msg, "(" #a ")")
#define assert_not_negativem(a) _CHGen1P(assert_not_negative, msg, "(" #a ")")
#define assert_not_positivem(a) _CHGen1P(assert_not_positive, msg, "(" #a ")")
#define assert_negativem(a)     _CHGen1P(assert_negative    , msg, "(" #a ")")

#define assert_str_equal(a, b) ch_assert_str_equal(a, b, _CH_CEPS(NULL, "assert_str_equal(" #a ", " #b ")"))
#define assert_str_not_equal(a, b) ch_assert_str_not_equal(a, b, _CH_CEPS(NULL, "assert_str_not_equal(" #a ", " #b ")"))

#define assert_str_equalm(a, b, msg) ch_assert_str_equal(a, b, _CH_CEPS(msg, "assert_str_equal(" #a ", " #b ")"))
#define assert_str_not_equalm(a, b, msg) ch_assert_str_not_equal(a, b, _CH_CEPS(msg, "assert_str_not_equal(" #a ", " #b ")"))

#define assert_mem_equal(a, b, size) ch_assert_mem_equal(a, b, size, _CH_CEPS(NULL, "assert_str_equal(" #a ", " #b ", " size ")"))
#define assert_mem_not_equal(a, b, size) ch_assert_mem_not_equal(a, b, size, _CH_CEPS(NULL, "assert_str_not_equal(" #a ", " #b ", " #size ")"))

#define assert_mem_equalm(a, b, size, msg) ch_assert_mem_equal(a, b, size, _CH_CEPS(msg, "assert_str_equal(" #a ", " #b ", " size ")"))
#define assert_mem_not_equalm(a, b, size, msg) ch_assert_mem_not_equal(a, b, size, _CH_CEPS(msg, "assert_str_not_equal(" #a ", " #b ", " #size ")"))

#define assert_fail(a) ch_assert_fail(a, _CH_CEPS(NULL, "assert_fail(" #a ")"))

#define assert_failm(a, msg) ch_assert_fail(a, _CH_CEPS(msg, "assert_fail(" #a ")"))

#define assert_fail_with(a, b) ch_assert_fail_with(a, b, _CH_CEPS(NULL, "assert_fail(" #a ")"))

#define assert_fail_withm(a, b, msg) ch_assert_fail_with(a, b, _CH_CEPS(msg, "assert_fail(" #a ")"))

#endif /* INCLUDE_C_HACKER_H_ */
