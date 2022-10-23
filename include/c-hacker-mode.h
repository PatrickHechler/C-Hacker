/*
 * c-hacker-mode.h
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#ifndef INCLUDE_C_HACKER_MODE_H_
#define INCLUDE_C_HACKER_MODE_H_

/* implement the C-Hacker API with the library calls of the c-hacker.so or c-hacker.a file */
#define C_HACKER_MODE_LIBARY        1
/* implement the C-Hacker API with 'static' functions */
#define C_HACKER_MODE_STATIC        2
/* implement the C-Hacker API with 'static inline' functions */
#define C_HACKER_MODE_STATIC_INLINE 3

/*
 * customize the implementation of the C-Hacker API
 *
 * when this mode is used the defines
 *   - CH_VAR(var)
 *     - a variable declaration
 *   - CH_PREFIX
 *     - the prefix of a function declaration
 *   - CH_PARAMS(params)
 *     - the parameters of a function declaration
 *   - CH_PN(name)
 *     - the name of a parameter in a function declaration
 *   - CH_IMPL(impl)
 *     - the implementation of a function
 *   - CH_ERROR
 *     - executed on failure
 * has too be made manually
 */
#define C_HACKER_MODE_CUSTOM        4

// defines for mode=C_HACKER_MODE_LIBARY
#define _CH_L_VAR(var)                                extern var;
#define _CH_L_PREFIX                                  extern void
#define _CH_L_PARAMS(params)                          params
#define _CH_L_PN(name)                                name
#define _CH_L_IMPL(impl)                              ;
#define _CH_L_ERROR(msg,file_name,line_num,value_str) ch_fail(msg, file_name, line_num, value_str);
// defines for mode=C_HACKER_MODE_STATIC
#define _CH_S_VAR(var)                                static var;
#define _CH_S_PREFIX                                  static void
#define _CH_S_PARAMS(params)                          params
#define _CH_S_PN(name)                                name
#define _CH_S_IMPL(impl)                              { impl }
#define _CH_S_ERROR(msg,file_name,line_num,value_str) ch_fail(msg, file_name, line_num, value_str);
// defines for mode=C_HACKER_MODE_STATIC_INLINE
#define _CH_SI_VAR(var)                               static var;
#define _CH_SI_PREFIX                                 static inline void
#define _CH_SI_PARAMS(params)                         params
#define _CH_SI_PN(name)                               name
#define _CH_SI_IMPL(impl)                             { impl }
#define _CH_SI_ERROR(msg,file_name,line_num,value_str)_ch_fail(msg, file_name, line_num, value_str);

#endif /* INCLUDE_C_HACKER_MODE_H_ */
