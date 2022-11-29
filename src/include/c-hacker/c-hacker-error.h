/*
 * c-hacker-error.h
 *
 *  Created on: Nov 21, 2022
 *      Author: pat
 */

#ifndef SRC_INCLUDE_C_HACKER_C_HACKER_ERROR_H_
#define SRC_INCLUDE_C_HACKER_C_HACKER_ERROR_H_

struct c_hacker_error {
	const char *file;
	long line;
	const char *exp;
	const char *msg;
};

#endif /* SRC_INCLUDE_C_HACKER_C_HACKER_ERROR_H_ */
