/*
 * c-hacker-fails.h
 *
 *  Created on: Oct 24,2022
 *      Author: pat
 */

#ifndef INCLUDE_C_HACKER_FAILS_H_
#define INCLUDE_C_HACKER_FAILS_H_

enum c_hacker_fail_code {
	chf_fail_call = 1, // chf_fail_call is used when fail is called

	chf_equal, chf_not_equal, chf_greater, chf_greater_equal, chf_less_equal, chf_less,

	chf_zero, chf_not_zero, chf_positive, chf_not_negative, chf_not_positive, chf_negative,

	chf_str_equal, chf_str_not_equal,

	chf_mem_equal, chf_mem_not_equal,

	chf_fail, // chf_fail is used when assert_fail failed because a did not fail or failed with the wrong code

};

#endif /* INCLUDE_C_HACKER_FAILS_H_ */
