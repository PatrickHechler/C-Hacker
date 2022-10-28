/*
 * c-hacker-set-mode.h
 *
 * including this file will set the mode to the current C_HACKER_MODE
 * if C_HACKER_MODE is not set C_HACKER_MODE_LIBARY will be used
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#ifndef INCLUDE_C_HACKER_SET_MODE_H_
#define INCLUDE_C_HACKER_SET_MODE_H_

#include "c-hacker-mode.h"

#ifndef C_HACKER_MODE
#define C_HACKER_MODE C_HACKER_MODE_LIBARY
#endif

#if C_HACKER_MODE == C_HACKER_MODE_LIBARY
#define CH_VAR(var)                                      _CH_L_VAR(var)
#define CH_PREFIX                                        _CH_L_PREFIX
#define CH_PARAMS(params)                                _CH_L_PARAMS(params)
#define CH_PN(name)                                      _CH_L_PN(name)
#define CH_IMPL(impl)                                    _CH_L_IMPL(impl)
#define CH_ERROR(msg,file_name,line_num,value_str)       _CH_L_ERROR(msg,file_name,line_num,value_str)
#elif C_HACKER_MODE == C_HACKER_MODE_STATIC
#define CH_VAR(var)                                      _CH_S_VAR(var)
#define CH_PREFIX                                        _CH_S_PREFIX
#define CH_PARAMS(params)                                _CH_S_PARAMS(params)
#define CH_PN(name)                                      _CH_S_PN(name)
#define CH_IMPL(impl)                                    _CH_S_IMPL(impl)
#define CH_ERROR                                         _CH_S_ERROR(msg,file_name,line_num,value_str)
#elif C_HACKER_MODE == C_HACKER_MODE_STATIC_INLINE
#define CH_VAR(var)                                      _CH_SI_VAR(var)
#define CH_PREFIX                                        _CH_SI_PREFIX
#define CH_PARAMS(params)                                _CH_SI_PARAMS(params)
#define CH_PN(name)                                      _CH_SI_PN(name)
#define CH_IMPL(impl)                                    _CH_SI_IMPL(impl)
#define CH_ERROR(msg,file_name,line_num,value_str)       _CH_SI_ERROR(msg,file_name,line_num,value_str)
#elif C_HACKER_MODE == C_HACKER_MODE_CUSTOM
#ifndef CH_VAR
#error "C_HACKER_MODE=C_HACKER_MODE_CUSTOM, but CH_VAR is not defined!"
#endif
#ifndef CH_PREFIX
#error "C_HACKER_MODE=C_HACKER_MODE_CUSTOM, but CH_PREFIX is not defined!"
#endif
#ifndef CH_PARAMS
#error "C_HACKER_MODE=C_HACKER_MODE_CUSTOM, but CH_PARAMS is not defined!"
#endif
#ifndef CH_PN
#error "C_HACKER_MODE=C_HACKER_MODE_CUSTOM, but CH_PN is not defined!"
#endif
#ifndef CH_IMPL
#error "C_HACKER_MODE=C_HACKER_MODE_CUSTOM, but CH_IMPL is not defined!"
#endif
#ifndef CH_ERROR
#error "C_HACKER_MODE=C_HACKER_MODE_CUSTOM, but CH_ERROR is not defined!"
#endif
#else
#error "unknown C_HACKER_MODE!"
#endif

#endif /* INCLUDE_C_HACKER_SET_MODE_H_ */
