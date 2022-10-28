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

static void setup(int argc, char **argv);

static void read_checks(void);

static void *lib;

static char **check_name;
static void (**start_all_checks)(void);
static void (**start_checks)(void);
static void (**end_all_checks)(void);
static void (**end_checks)(void);
static void (**checks)(void);

int main(int argc, char **argv) {
	setup(argc, argv);
	read_cheks();
	return 0;
}

static void setup(int argc, char **argv) {
	if (!argv[1]) {
		fprintf(stderr, "not enough args!\n");
		exit(1);
	}
	if (argv[2]) {
		fprintf(stderr, "too many args!\n");
		exit(1);
	}
	lib = dlmopen(LM_ID_NEWLM, argv[1], RTLD_LAZY);
	if (!lib) {
		fprintf(stderr, "error on dlmopen: %s\n", dlerror());
		exit(1);
	}
}

static void read_checks(void) {

}
