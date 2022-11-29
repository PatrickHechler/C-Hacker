/*
 * c-hacker.h
 *
 *  Created on: Nov 21, 2022
 *      Author: pat
 */

#ifndef SRC_INCLUDE_C_HACKER_C_HACKER_H_
#define SRC_INCLUDE_C_HACKER_C_HACKER_H_

#include <stddef.h>

extern void ch_fail(const char *file, long line, const char *exp,
		const char *msg);

#define failm(msg) ch_fail(__FILE__, __LINE__, "failm(" #msg ")")
#define fail() ch_fail(__FILE__, __LINE__, "fail()")

extern void ch_assert_fail(void (*func)(void), const char *file, long line,
		const char *exp, const char *msg);

#define assert_failm(func,msg) ch_assert_fail(func,__FILE__, __LINE__, "assert_failm(" #func ", " #msg ")")
#define assert_fail(func) ch_assert_fail(func,__FILE__, __LINE__, "assert_fail(" #func ")")

extern void ch_assert_equal_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_equalm_ll(a,b,msg) ch_assert_equal_ll(a,b,__FILE__, __LINE__, "assert_equalm_ll(" #a ", " #b ", " #msg ")")
#define assert_equal_ll(a,b) ch_assert_equal_ll(a,b,__FILE__, __LINE__, "assert_equal_ll(" #a ", " #b ")")

extern void ch_assert_equal_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_equalm_l(a,b,msg) ch_assert_equal_l(a,b,__FILE__, __LINE__, "assert_equalm_l(" #a ", " #b ", " #msg ")")
#define assert_equal_l(a,b) ch_assert_equal_l(a,b,__FILE__, __LINE__, "assert_equal_l(" #a ", " #b ")")

extern void ch_assert_equal_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_equalm_i(a,b,msg) ch_assert_equal_i(a,b,__FILE__, __LINE__, "assert_equalm_i(" #a ", " #b ", " #msg ")")
#define assert_equal_i(a,b) ch_assert_equal_i(a,b,__FILE__, __LINE__, "assert_equal_i(" #a ", " #b ")")

extern void ch_assert_equal_s(short a, short b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_equalm_s(a,b,msg) ch_assert_equal_s(a,b,__FILE__, __LINE__, "assert_equalm_s(" #a ", " #b ", " #msg ")")
#define assert_equal_s(a,b) ch_assert_equal_s(a,b,__FILE__, __LINE__, "assert_equal_s(" #a ", " #b ")")

extern void ch_assert_equal_c(short a, short b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_equalm_c(a,b,msg) ch_assert_equal_c(a,b,__FILE__, __LINE__, "assert_equalm_c(" #a ", " #b ", " #msg ")")
#define assert_equal_c(a,b) ch_assert_equal_c(a,b,__FILE__, __LINE__, "assert_equal_c(" #a ", " #b ")")

extern void ch_assert_equal_p(void *a, void *b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_equalm_p(a,b,msg) ch_assert_equal_p(a,b,__FILE__, __LINE__, "assert_equalm_p(" #a ", " #b ", " #msg ")")
#define assert_equal_p(a,b) ch_assert_equal_p(a,b,__FILE__, __LINE__, "assert_equal_p(" #a ", " #b ")")

extern void ch_assert_equal_f(float a, float b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_equalm_f(a,b,msg) ch_assert_equal_f(a,b,__FILE__, __LINE__, "assert_equalm_f(" #a ", " #b ", " #msg ")")
#define assert_equal_f(a,b) ch_assert_equal_f(a,b,__FILE__, __LINE__, "assert_equal_f(" #a ", " #b ")")

extern void ch_assert_equal_d(double a, double b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_equalm_d(a,b,msg) ch_assert_equal_d(a,b,__FILE__, __LINE__, "assert_equalm_d(" #a ", " #b ", " #msg ")")
#define assert_equal_d(a,b) ch_assert_equal_d(a,b,__FILE__, __LINE__, "assert_equal_d(" #a ", " #b ")")

extern void ch_assert_equal_ld(long double a, long double b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_equalm_ld(a,b,msg) ch_assert_equal_ld(a,b,__FILE__, __LINE__, "assert_equalm_ld(" #a ", " #b ", " #msg ")")
#define assert_equal_ld(a,b) ch_assert_equal_ld(a,b,__FILE__, __LINE__, "assert_equal_ld(" #a ", " #b ")")

extern void ch_assert_not_equal_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_not_equalm_ll(a,b,msg) ch_assert_not_equal_ll(a,b,__FILE__, __LINE__, "assert_not_equalm_ll(" #a ", " #b ", " #msg ")")
#define assert_not_equal_ll(a,b) ch_assert_not_equal_ll(a,b,__FILE__, __LINE__, "assert_not_equal_ll(" #a ", " #b ")")

extern void ch_assert_not_equal_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_not_equalm_l(a,b,msg) ch_assert_not_equal_l(a,b,__FILE__, __LINE__, "assert_not_equalm_l(" #a ", " #b ", " #msg ")")
#define assert_not_equal_l(a,b) ch_assert_not_equal_l(a,b,__FILE__, __LINE__, "assert_not_equal_l(" #a ", " #b ")")

extern void ch_assert_not_equal_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_not_equalm_i(a,b,msg) ch_assert_not_equal_i(a,b,__FILE__, __LINE__, "assert_not_equalm_i(" #a ", " #b ", " #msg ")")
#define assert_not_equal_i(a,b) ch_assert_not_equal_i(a,b,__FILE__, __LINE__, "assert_not_equal_i(" #a ", " #b ")")

extern void ch_assert_not_equal_s(short a, short b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_not_equalm_s(a,b,msg) ch_assert_not_equal_s(a,b,__FILE__, __LINE__, "assert_not_equalm_s(" #a ", " #b ", " #msg ")")
#define assert_not_equal_s(a,b) ch_assert_not_equal_s(a,b,__FILE__, __LINE__, "assert_not_equal_s(" #a ", " #b ")")

extern void ch_assert_not_equal_c(short a, short b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_not_equalm_c(a,b,msg) ch_assert_not_equal_c(a,b,__FILE__, __LINE__, "assert_not_equalm_c(" #a ", " #b ", " #msg ")")
#define assert_not_equal_c(a,b) ch_assert_not_equal_c(a,b,__FILE__, __LINE__, "assert_not_equal_c(" #a ", " #b ")")

extern void ch_assert_not_equal_p(void *a, void *b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_not_equalm_p(a,b,msg) ch_assert_not_equal_p(a,b,__FILE__, __LINE__, "assert_not_equalm_p(" #a ", " #b ", " #msg ")")
#define assert_not_equal_p(a,b) ch_assert_not_equal_p(a,b,__FILE__, __LINE__, "assert_not_equal_p(" #a ", " #b ")")

extern void ch_assert_not_equal_f(float a, float b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_not_equalm_f(a,b,msg) ch_assert_not_equal_f(a,b,__FILE__, __LINE__, "assert_not_equalm_f(" #a ", " #b ", " #msg ")")
#define assert_not_equal_f(a,b) ch_assert_not_equal_f(a,b,__FILE__, __LINE__, "assert_not_equal_f(" #a ", " #b ")")

extern void ch_assert_not_equal_d(double a, double b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_not_equalm_d(a,b,msg) ch_assert_not_equal_d(a,b,__FILE__, __LINE__, "assert_not_equalm_d(" #a ", " #b ", " #msg ")")
#define assert_not_equal_d(a,b) ch_assert_not_equal_d(a,b,__FILE__, __LINE__, "assert_not_equal_d(" #a ", " #b ")")

extern void ch_assert_not_equal_ld(long double a, long double b,
		const char *file, long line, const char *exp, const char *msg);

#define assert_not_equalm_ld(a,b,msg) ch_assert_not_equal_ld(a,b,__FILE__, __LINE__, "assert_not_equalm_ld(" #a ", " #b ", " #msg ")")
#define assert_not_equal_ld(a,b) ch_assert_not_equal_ld(a,b,__FILE__, __LINE__, "assert_not_equal_ld(" #a ", " #b ")")

extern void ch_assert_less_equal_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_less_equalm_ll(a,b,msg) ch_assert_less_equal_ll(a,b,__FILE__, __LINE__, "assert_less_equalm_ll(" #a ", " #b ", " #msg ")")
#define assert_less_equal_ll(a,b) ch_assert_less_equal_ll(a,b,__FILE__, __LINE__, "assert_less_equal_ll(" #a ", " #b ")")

extern void ch_assert_less_equal_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_less_equalm_l(a,b,msg) ch_assert_less_equal_l(a,b,__FILE__, __LINE__, "assert_less_equalm_l(" #a ", " #b ", " #msg ")")
#define assert_less_equal_l(a,b) ch_assert_less_equal_l(a,b,__FILE__, __LINE__, "assert_less_equal_l(" #a ", " #b ")")

extern void ch_assert_less_equal_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_less_equalm_i(a,b,msg) ch_assert_less_equal_i(a,b,__FILE__, __LINE__, "assert_less_equalm_i(" #a ", " #b ", " #msg ")")
#define assert_less_equal_i(a,b) ch_assert_less_equal_i(a,b,__FILE__, __LINE__, "assert_less_equal_i(" #a ", " #b ")")

extern void ch_assert_less_equal_s(short a, short b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_less_equalm_s(a,b,msg) ch_assert_less_equal_s(a,b,__FILE__, __LINE__, "assert_less_equalm_s(" #a ", " #b ", " #msg ")")
#define assert_less_equal_s(a,b) ch_assert_less_equal_s(a,b,__FILE__, __LINE__, "assert_less_equal_s(" #a ", " #b ")")

extern void ch_assert_less_equal_c(short a, short b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_less_equalm_c(a,b,msg) ch_assert_less_equal_c(a,b,__FILE__, __LINE__, "assert_less_equalm_c(" #a ", " #b ", " #msg ")")
#define assert_less_equal_c(a,b) ch_assert_less_equal_c(a,b,__FILE__, __LINE__, "assert_less_equal_c(" #a ", " #b ")")

extern void ch_assert_less_equal_p(void *a, void *b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_less_equalm_p(a,b,msg) ch_assert_less_equal_p(a,b,__FILE__, __LINE__, "assert_less_equalm_p(" #a ", " #b ", " #msg ")")
#define assert_less_equal_p(a,b) ch_assert_less_equal_p(a,b,__FILE__, __LINE__, "assert_less_equal_p(" #a ", " #b ")")

extern void ch_assert_less_equal_f(float a, float b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_less_equalm_f(a,b,msg) ch_assert_less_equal_f(a,b,__FILE__, __LINE__, "assert_less_equalm_f(" #a ", " #b ", " #msg ")")
#define assert_less_equal_f(a,b) ch_assert_less_equal_f(a,b,__FILE__, __LINE__, "assert_less_equal_f(" #a ", " #b ")")

extern void ch_assert_less_equal_d(double a, double b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_less_equalm_d(a,b,msg) ch_assert_less_equal_d(a,b,__FILE__, __LINE__, "assert_less_equalm_d(" #a ", " #b ", " #msg ")")
#define assert_less_equal_d(a,b) ch_assert_less_equal_d(a,b,__FILE__, __LINE__, "assert_less_equal_d(" #a ", " #b ")")

extern void ch_assert_less_equal_ld(long double a, long double b,
		const char *file, long line, const char *exp, const char *msg);

#define assert_less_equalm_ld(a,b,msg) ch_assert_less_equal_ld(a,b,__FILE__, __LINE__, "assert_less_equalm_ld(" #a ", " #b ", " #msg ")")
#define assert_less_equal_ld(a,b) ch_assert_less_equal_ld(a,b,__FILE__, __LINE__, "assert_less_equal_ld(" #a ", " #b ")")

extern void ch_assert_less_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_lessm_ll(a,b,msg) ch_assert_less_ll(a,b,__FILE__, __LINE__, "assert_lessm_ll(" #a ", " #b ", " #msg ")")
#define assert_less_ll(a,b) ch_assert_less_ll(a,b,__FILE__, __LINE__, "assert_less_ll(" #a ", " #b ")")

extern void ch_assert_less_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_lessm_l(a,b,msg) ch_assert_less_l(a,b,__FILE__, __LINE__, "assert_lessm_l(" #a ", " #b ", " #msg ")")
#define assert_less_l(a,b) ch_assert_less_l(a,b,__FILE__, __LINE__, "assert_less_l(" #a ", " #b ")")

extern void ch_assert_less_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_lessm_i(a,b,msg) ch_assert_less_i(a,b,__FILE__, __LINE__, "assert_lessm_i(" #a ", " #b ", " #msg ")")
#define assert_less_i(a,b) ch_assert_less_i(a,b,__FILE__, __LINE__, "assert_less_i(" #a ", " #b ")")

extern void ch_assert_less_s(short a, short b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_lessm_s(a,b,msg) ch_assert_less_s(a,b,__FILE__, __LINE__, "assert_lessm_s(" #a ", " #b ", " #msg ")")
#define assert_less_s(a,b) ch_assert_less_s(a,b,__FILE__, __LINE__, "assert_less_s(" #a ", " #b ")")

extern void ch_assert_less_c(short a, short b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_lessm_c(a,b,msg) ch_assert_less_c(a,b,__FILE__, __LINE__, "assert_lessm_c(" #a ", " #b ", " #msg ")")
#define assert_less_c(a,b) ch_assert_less_c(a,b,__FILE__, __LINE__, "assert_less_c(" #a ", " #b ")")

extern void ch_assert_less_p(void *a, void *b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_lessm_p(a,b,msg) ch_assert_less_p(a,b,__FILE__, __LINE__, "assert_lessm_p(" #a ", " #b ", " #msg ")")
#define assert_less_p(a,b) ch_assert_less_p(a,b,__FILE__, __LINE__, "assert_less_p(" #a ", " #b ")")

extern void ch_assert_less_f(float a, float b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_lessm_f(a,b,msg) ch_assert_less_f(a,b,__FILE__, __LINE__, "assert_lessm_f(" #a ", " #b ", " #msg ")")
#define assert_less_f(a,b) ch_assert_less_f(a,b,__FILE__, __LINE__, "assert_less_f(" #a ", " #b ")")

extern void ch_assert_less_d(double a, double b, const char *file, long line,
		const char *exp, const char *msg);

#define assert_lessm_d(a,b,msg) ch_assert_less_d(a,b,__FILE__, __LINE__, "assert_lessm_d(" #a ", " #b ", " #msg ")")
#define assert_less_d(a,b) ch_assert_less_d(a,b,__FILE__, __LINE__, "assert_less_d(" #a ", " #b ")")

extern void ch_assert_less_ld(long double a, long double b, const char *file,
		long line, const char *exp, const char *msg);

#define assert_lessm_ld(a,b,msg) ch_assert_less_ld(a,b,__FILE__, __LINE__, "assert_lessm_ld(" #a ", " #b ", " #msg ")")
#define assert_less_ld(a,b) ch_assert_less_ld(a,b,__FILE__, __LINE__, "assert_less_ld(" #a ", " #b ")")

#include <setjmp.h>

#ifndef SRC_LIB_C_HACKER_C_
jmp_buf *c_hacker_state;
#endif

#endif /* SRC_INCLUDE_C_HACKER_C_HACKER_H_ */
