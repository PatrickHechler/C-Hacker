/*
 * c-hacker-fails.h
 *
 *  Created on: Oct 24,2022
 *      Author: pat
 */

#ifndef INCLUDE_C_HACKER_TYPES_H_
#define INCLUDE_C_HACKER_TYPES_H_

#include <setjmp.h>

enum c_hacker_fail_code {
	chf_none = 0,

	chf_fail_call, // chf_fail_call is used when fail is called

	chf_equal,
	chf_not_equal,
	chf_greater,
	chf_greater_equal,
	chf_less_equal,
	chf_less,

	chf_zero,
	chf_not_zero,
	chf_positive,
	chf_not_negative,
	chf_not_positive,
	chf_negative,

	chf_str_equal,
	chf_str_not_equal,

	chf_mem_equal,
	chf_mem_not_equal,

	chf_fail, // chf_fail is used when assert_fail failed because a did not fail or failed with the wrong code
};

union ch_value {
	const char *str;
	const void *pntr;
	long long numll;
	long double numld;
};

struct c_hacker_info {
	char *check_name;
	const char *file_name;
	long line_num;
	const char *val_str;
	const char *msg;
	jmp_buf *state_pntr;
	union ch_value value_a;
	union ch_value value_b;
};

typedef struct c_hacker_info ch_info;

#endif /* INCLUDE_C_HACKER_TYPES_H_ */
