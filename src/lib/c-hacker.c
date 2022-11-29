/*
 * c-hacker.c
 *
 *  Created on: Nov 20, 2022
 *      Author: pat
 */
#define SRC_LIB_C_HACKER_C_
#include "../include/c-hacker/c-hacker.h"
#include "../include/c-hacker/c-hacker-error.h"

#include <dlfcn.h>

extern void ch_fail(const char *file, long line, const char *exp,
		const char *msg) {
	jmp_buf **c_hacker_state = dlsym(RTLD_DEFAULT, "c_hacker_state");
	struct c_hacker_error *c_hacker_error = dlsym(RTLD_DEFAULT,
			"c_hacker_error");
	c_hacker_error->file = file;
	c_hacker_error->line = line;
	c_hacker_error->exp = exp;
	c_hacker_error->msg = msg;
	longjmp(**c_hacker_state, 1);
}

extern void ch_assert_fail(void (*func)(void), const char *file, long line,
		const char *exp, const char *msg) {
	jmp_buf **c_hacker_state = dlsym(RTLD_DEFAULT, "c_hacker_state");
	jmp_buf *old = *c_hacker_state;
	if (setjmp(**c_hacker_state)) {
		*c_hacker_state = old;
	} else {
		func();
		*c_hacker_state = old;
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_s(short a, short b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_c(short a, short b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_p(void *a, void *b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_f(float a, float b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_d(double a, double b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_equal_ld(long double a, long double b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a == b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_s(short a, short b, const char *file, long line,
		const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_c(short a, short b, const char *file, long line,
		const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_p(void *a, void *b, const char *file, long line,
		const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_f(float a, float b, const char *file, long line,
		const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_d(double a, double b, const char *file,
		long line, const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_not_equal_ld(long double a, long double b,
		const char *file, long line, const char *exp, const char *msg) {
		if (!(a != b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_s(short a, short b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_c(short a, short b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_p(void *a, void *b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_f(float a, float b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_d(double a, double b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_equal_ld(long double a, long double b,
		const char *file, long line, const char *exp, const char *msg) {
	if (!(a <= b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_ll(long long a, long long b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_l(long a, long b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_i(int a, int b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_s(short a, short b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_c(short a, short b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_p(void *a, void *b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_f(float a, float b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_d(double a, double b, const char *file, long line,
		const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}

extern void ch_assert_less_ld(long double a, long double b, const char *file,
		long line, const char *exp, const char *msg) {
	if (!(a < b)) {
		ch_fail(file, line, exp, msg);
	}
}
