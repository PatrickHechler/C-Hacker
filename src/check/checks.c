/*
 * checks.c
 *
 *  Created on: Nov 20, 2022
 *      Author: pat
 */

#include "../include/c-hacker/c-hacker.h"
#include <stdio.h>

CHECK nop() {
}

CHECK hello_world() {
	puts("hello world");
}

void failure() {
	fail();
}

CHECK check_fail() {
	puts("check fail now");
	assert_fail(failure);
	puts("checked fail");
}
