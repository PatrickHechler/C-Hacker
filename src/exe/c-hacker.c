/*
 * c-hacker.c
 *
 *  Created on: Nov 20, 2022
 *      Author: pat
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

static inline void setup(int, char**, char**, char**, char**);
static inline void compile(char*, char*, char*);
static inline void execute_check(char*);
static inline void wait_for_normal_exit(pid_t pid);
static inline void parse_check(const char *in, const char *out) __attribute__((noreturn));

static _Bool no_exe = 0;
static _Bool use_static_c_hacker = 0;
static _Bool generate_obj_file = 0;
static _Bool no_include = 0;
static const char *func_prefix = NULL;

int main(int argc, char **argv) {
	char *in, *out0, *out1;
	setup(argc, argv, &in, &out0, &out1);
	compile(in, out0, out1);
	execute_check(out1);
}

static inline void setup(int argc, char **argv, char **in, char **out0,
		char **out1) {
	if (argc < 3) {
		fprintf(stderr,
				"Usage: c-hacker [OPTIONS] TEST_SOURCE_FILE BINARY_FOLDER\n");
		exit(1);
	}
	for (; argc > 3; argc--, argv++) {
		if (strcmp("--no-exe", *argv)) {
			no_exe = 1;
		} else if (strcmp("--no-include", *argv)) {
			no_include = 1;
		} else if (strcmp("--static-c-hacker", *argv)) {
			use_static_c_hacker = 1;
		} else if (strcmp("--gen-obj", *argv)) {
			generate_obj_file = 1;
			no_exe = 1;
		} else if (memcmp("--func-pre=", *argv, 11)) {
			func_prefix = *argv + 11;
		} else {
			fprintf(stderr, "illegal Option: '%s'\n", *argv);
			exit(1);
		}
	}
	char *name = strrchr(argv[1], '/');
	name = name ? name + 1 : argv[1];
	size_t bin_folder_len = strlen(argv[2]);
	size_t bin_name_len = strlen(name);
	if (!strcmp(".c", name + bin_name_len - 2)) {
		bin_name_len -= 2;
	}
	size_t bin_len = bin_folder_len + bin_name_len + 1;
	char *bin_file = malloc(bin_len);
	if (!bin_file) {
		err(1, "could not allocate enugh memory for the binary file path!");
	}
	memcpy(bin_file, argv[2], bin_folder_len);
	memcpy(bin_file + bin_folder_len, name, bin_name_len);
	bin_file[bin_folder_len + bin_name_len] = '\0';
	char *out_file = malloc(bin_len + 2);
	if (!out_file) {
		err(1, "could not allocate enugh memory for the output file path!");
	}
	memcpy(out_file, bin_file, bin_name_len - 1);
	out_file[bin_name_len] = '.';
	out_file[bin_name_len + 1] = 'c';
	out_file[bin_name_len + 2] = '\0';
	*in = argv[1];
	*out0 = out_file;
	*out1 = bin_file;
}

static inline void compile(char *in, char *out0, char *out1) {
	pid_t cpid = fork();
	if (cpid == -1) {
		err(1, "could not fork");
	} else if (cpid == 0) {
		parse_check(in, out0);
	} else {
		wait_for_normal_exit(cpid);
	}
	cpid = fork();
	if (cpid == -1) {
		err(1, "could not fork");
	} else if (cpid == 0) {
		char **args =
				{ program_invocation_name,
						no_include ? "-I/usr/include/" : "-Iexp/include/", "-o",
						out1,
						generate_obj_file ? "-c" :
						use_static_c_hacker ?
								"-L~/git/C-Hacker/exp/static/libc-hacker.a" :
								"-L~/git/C-Hacker/exp/shared/libc-hacker.so",
						out0, NULL };
		execv(program_invocation_name, args);
	} else {
		wait_for_normal_exit(cpid);
	}
}

static inline void execute_check(char *check_file) {
	char *(args[]) = { check_file, NULL };
	execv(check_file, args);
}

static inline void wait_for_normal_exit(pid_t pid) {
	while (1) {
		int status;
		waitpid(pid, &status, 1);
		if (WIFCONTINUED(status) || WIFSTOPPED(status)) {
			continue;
		} else if (WIFSIGNALED(status)) {
			fprintf(stderr, "child terminated because of signal %d",
					WTERMSIG(status));
		} else if (WIFEXITED(status) && !WEXITSTATUS(status)) {
			return;
		} else if (WIFEXITED(status)) {
			fprintf(stderr, "child terminated with exit code %d",
					WEXITSTATUS(status));
		} else {
			fprintf(stderr, "unknown result of waitpid: %d", status);
		}
		exit(2);
	}
}

static inline void parse_check(const char *in, const char *out) {
	exit(1); // TODO
}
