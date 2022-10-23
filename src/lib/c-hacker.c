/*
 * c-hacker.c
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#include "../../include/c-hacker-mode.h"

#include <stdint-gcc.h>
#include <stdio.h>
#include <stdlib.h>

#define C_HACKER_MODE                              C_HACKER_MODE_CUSTOM
#define CH_VAR(var)                                var;
#define CH_PREFIX                                  _CH_L_PREFIX
#define CH_PARAMS(params)                          _CH_L_PARAMS(params)
#define CH_PN(name)                                _CH_L_PN(name)
#define CH_IMPL(impl)                              _CH_SI_IMPL(impl)
#define CH_ERROR(msg,file_name,line_num,value_str) _CH_L_ERROR(msg,file_name,line_num,value_str)

#include "../../include/c-hacker.h"

extern void f() {
	assert_equal(1, 2, "");
}
