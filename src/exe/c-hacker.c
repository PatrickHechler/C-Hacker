/*
 * c-hacker.c
 *
 *  Created on: Oct 23, 2022
 *      Author: pat
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <link.h>
#include <setjmp.h>
#include <string.h>

#include "../../include/c-hacker-types.h"

static void setup(int argc, char **argv);
static void read_checks(void);
static void execute_checks(void);

static void *lib;

static void (**start_all_checks)(void) = NULL;
static void (**start_checks)(void) = NULL;
static void (**end_all_checks)(void) = NULL;
static void (**end_checks)(void) = NULL;
static void (**checks)(void) = NULL;

static int executed_check_count;
static int good_check_count;

static char **fail_msgs;

ch_info ch_inf;

int main(int argc, char **argv) {
	setup(argc, argv);
	read_checks();
	execute_checks();
	dlclose(lib);
	fflush(NULL);
	printf("executed %d checks, %d where good and %d failed.\n",
			executed_check_count, good_check_count,
			executed_check_count - good_check_count);
	for (; *fail_msgs; ++fail_msgs) {
		puts(*fail_msgs);
	}
	return executed_check_count - good_check_count;
}

static void setup(int argc, char **argv) {
	if (!argv[1]) {
		fprintf(stderr, "not enough args!\n");
		exit(1);
	}
	if (argv[2]) {
		fprintf(stderr, "too many args!\n");
		exit(1);
	} // LM_ID_NEWLM
	lib = dlmopen(LM_ID_BASE, argv[1], RTLD_NOW | RTLD_GLOBAL);
	if (!lib) {
		fprintf(stderr, "error on dlmopen: %s\n", dlerror());
		exit(1);
	}
}

/*
 * may be done better in the future, but this is compatible with all shared objects
 * and does not require reading information of the ELF
 * (the shared object API does not provide a function to get a symbol with an unknown name)
 */
static void read_checks(void) {
	start_all_checks = malloc(sizeof(void*) * 2);
	start_all_checks[0] = dlsym(lib, "start_all");
	start_all_checks[1] = NULL;
	start_checks = malloc(sizeof(void*) * 2);
	start_checks[0] = dlsym(lib, "start");
	start_checks[1] = NULL;
	end_all_checks = malloc(sizeof(void*) * 2);
	end_all_checks[0] = dlsym(lib, "end_all");
	end_all_checks[1] = NULL;
	end_checks = malloc(sizeof(void*) * 2);
	end_checks[0] = dlsym(lib, "end");
	end_checks[1] = NULL;
	checks = dlsym(lib, "checks");
}

static const char* codestr(enum c_hacker_fail_code code) {
	switch (code) {
	case chf_none:
		return "<NONE>";
	case chf_fail_call:
		return "<FAIL>";
	case chf_equal:
		return "<ASSERTED-EQUAL>";
	case chf_not_equal:
		return "<ASSERTED-NOT-EQUAL>";
	case chf_greater:
		return "<ASSERTED-GREATER>";
	case chf_greater_equal:
		return "<ASSERTED-NOT-GREATER>";
	case chf_less_equal:
		return "<ASSERTED-LESS-EQUAL>";
	case chf_less:
		return "<ASSERTED-LESS>";
	case chf_zero:
		return "<ASSERTED-ZERO>";
	case chf_not_zero:
		return "<ASSERTED-NOT-ZERO>";
	case chf_positive:
		return "<ASSERTED-POSITIVE>";
	case chf_not_negative:
		return "<ASSERTED-NOT-NEGATIVE>";
	case chf_not_positive:
		return "<ASSERTED-NOT-POSITIVE>";
	case chf_negative:
		return "<ASSERTED-NEGATIVE>";
	case chf_str_equal:
		return "<ASSERTED-STR-EQUAL>";
	case chf_str_not_equal:
		return "<ASSERTED-STR-NOT-EQUAL>";
	case chf_mem_equal:
		return "<ASSERTED-MEM-EQUAL>";
	case chf_mem_not_equal:
		return "<ASSERTED-MEM-NOT-EQUAL>";
	case chf_fail:
		return "<ASSERTED-FAIL>";
	default:
		size_t len = snprintf(NULL, 0, "<UNKNOWN: 0x%X>", code);
		char *res = malloc(len + 1);
		snprintf(res, len + 1, "<UNKNOWN: 0x%X>", code);
		return res;
	}
}

static void execute_checks(void) {
	printf("[C-Hacker.execute_checks]: ch_inf.state_pntr=%p\n", ch_inf.state_pntr);
	fail_msgs = malloc(sizeof(const char*));
	fail_msgs[0] = NULL;
	int failed_names_index = 0;
	jmp_buf state;
	ch_inf.state_pntr = &state;
	executed_check_count = 0;
	good_check_count = 0;
	ch_inf.check_name = NULL;
	for (void (**sa)(void) = start_all_checks; *sa; sa++) {
		printf("[C-Hacker.execute_checks]: ch_inf.state_pntr=%p\n", ch_inf.state_pntr);
		(*sa)();
	}
	for (void (**c)(void) = checks; *c; c++) {
		ch_inf.check_name = "<unknown>";
		enum c_hacker_fail_code res = setjmp(*ch_inf.state_pntr);
		if (res == chf_none) {
			for (void (**s)(void) = start_checks; *s; s++) {
				printf("[C-Hacker.execute_checks]: ch_inf.state_pntr=%p\n", ch_inf.state_pntr);
				(*s)();
			}
			printf("[C-Hacker.execute_checks]: ch_inf.state_pntr=%p\n", ch_inf.state_pntr);
			(*c)();
			for (void (**e)(void) = end_checks; *e; e++) {
				printf("[C-Hacker.execute_checks]: ch_inf.state_pntr=%p\n", ch_inf.state_pntr);
				(*e)();
			}
			good_check_count++;
		} else {
			const char *unformatted;
			if (ch_inf.msg) {
				unformatted = "    check '%s' failed with code: %s\n"
				/*		    */"      failed at %s:%ld > %s\n"
						/*  */"      msg: '%s'";
			} else {
				unformatted = "    check '%s' failed with code: %s\n"
				/*		    */"      failed at %s:%ld > %s";
			}
			size_t len = snprintf(NULL, 0, unformatted, ch_inf.check_name,
					codestr(res), ch_inf.file_name, ch_inf.line_num, ch_inf.val_str,
					ch_inf.msg);
			fail_msgs[failed_names_index] = malloc(len + 1);
			snprintf(fail_msgs[failed_names_index], len + 1, unformatted,
					ch_inf.check_name, codestr(res), ch_inf.file_name,
					ch_inf.line_num, ch_inf.val_str, ch_inf.msg);
			fail_msgs = realloc(fail_msgs,
					sizeof(const char*) * (++failed_names_index));
			fail_msgs[failed_names_index] = NULL;
		}
		fflush(stdout);
		executed_check_count++;
	}
	ch_inf.check_name = NULL;
	for (void (**ea)(void) = end_all_checks; *ea; ea++) {
		(*ea)();
	}
}
