/*
 * c-hacker.c
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#include "../../include/c-hacker-mode.h"

#define C_HACKER_DO_INCLUDES

#define C_HACKER_MODE                                             C_HACKER_MODE_CUSTOM
#define CH_VAR(var)                                               var;
#define CH_PREFIX                                                 _CH_L_PREFIX
#define CH_PARAMS(params)                                         _CH_L_PARAMS(params)
#define CH_PN(name)                                               _CH_L_PN(name)
#define CH_IMPL(impl)                                             _CH_S_IMPL(impl)
#define CH_ERROR(msg,file_name,line_num,value_str,code,a,aa,b,bb) _CH_L_ERROR(msg,file_name,line_num,value_str,code,a,aa,b,bb)

#include <stdio.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/c-hacker.h"
