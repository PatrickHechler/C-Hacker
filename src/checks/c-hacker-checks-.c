/*
 * c-hacker-checks.c
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#include "../../include/c-hacker.h"

void start_all() {
	puts("start all checks");
}

void end_all() {
	puts("end all checks");
}

void start() {
	puts("check starts");
}

void end() {
	puts("check ended");
}

check(sample_check)
	fputs("this is a sample check which only prints this message.\n", stdout);
}

static void assert_equal_fails0() {
	assert_equal(-8, 12);
}

static void assert_equal_fails1() {
	assert_equalm(5, 7, "my message");
}

static void assert_equal_fails2() {
	assert_equal(((char)5), (unsigned char) 0);
}

static void assert_equal_fails3() {
	assert_equal(5.0, 5.1);
}

static void assert_equal_fails4() {
	assert_equal(-1, 1);
}

check(assert_equal_check)
	assert_equal(5, 5);
	assert_equal(0, 0);
	assert_equal(-0, 0);
	assert_equal((char) 0, (long) 0);
	assert_equal(0.0, 0.0);
	assert_fail(assert_equal_fails0);
	assert_equal(ch_inf.line_num, 34);
	assert_str_equal(ch_inf.file_name, "/data/git/C-Hacker/src/checks/c-hacker-checks.c");
	assert_str_equal(ch_inf.msg, NULL);
	assert_str_equal(ch_inf.msg, "assert_equal(-8, 12)");
	assert_fail(assert_equal_fails1);
	assert_str_equal(ch_inf.val_str, "my message");
	assert_equal(ch_inf.line_num, 38);
	assert_fail(assert_equal_fails2);
	assert_equal(ch_inf.line_num, 42);
	assert_fail(assert_equal_fails3);
	assert_equal(ch_inf.line_num, 46);
	assert_fail(assert_equal_fails4);
	assert_equal(ch_inf.line_num, 50);
}

void (*checks[])(void) = {
		sample_check,
		assert_equal_check,
		NULL
};
