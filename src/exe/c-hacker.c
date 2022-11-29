/*
 * c-hacker.c
 *
 *  Created on: Nov 20, 2022
 *      Author: pat
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/wait.h>

static inline void setup(int, char**, char**, char**, char**);
static inline void compile(char*, char*, char*);
static inline void execute_check(char*);
static inline void wait_for_normal_exit(pid_t pid);
static inline void parse_check(const char *in, const char *out);

static _Bool starts_with(const char *start, const char *string);

static _Bool no_exe = 0;
static _Bool no_gen_exe = 0;
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
	if (starts_with("--check=", argv[1])) {
		if (argc != 2) {
			fprintf(stderr,
					"Usage: c-hacker [OPTIONS] CHECK_SOURCE_FILE BINARY_FOLDER\n"
							"or     c-hacker --check=CHECK_BINARY_FILE(:OTHER_CHECK_BINARY)*\n");
			exit(1);
		}
		char *arg = argv[1] + 8;
		for (;;) {
			char *end = strchr(arg, ':');
			if (end) {
				*end = '\0';
			}
			execute_check(arg);
			if (end) {
				arg = end + 1;
			} else {
				exit(0);
			}
		}
	}
	if (argc < 3) {
		fprintf(stderr,
				"Usage: c-hacker [OPTIONS] CHECK_SOURCE_FILE BINARY_FOLDER\n"
						"or     c-hacker --check=CHECK_BINARY_FILE(:OTHER_CHECK_BINARY)*\n");
		exit(1);
	}
	for (argv++; argc > 3; argc--, argv++) {
		if (!strcmp("--no-exe", *argv)) {
			no_exe = 1;
		} else if (!strcmp("--no-include", *argv)) {
			no_include = 1;
		} else if (!strcmp("--static-c-hacker", *argv)) {
			use_static_c_hacker = 1;
		} else if (!strcmp("--gen-obj", *argv)) {
			generate_obj_file = 1;
			no_exe = 1;
		} else if (!strcmp("--no-gen-exe", *argv)) {
			no_gen_exe = 1;
		} else if (starts_with("--func-pre=", *argv)) {
			func_prefix = *argv + 11;
		} else {
			fprintf(stderr, "illegal Option: '%s'\n", *argv);
			exit(1);
		}
	}
	argv--;
	if (!func_prefix) {
		func_prefix = "extern void ";
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
	memcpy(out_file, bin_file, bin_folder_len + bin_name_len);
	out_file[bin_folder_len + bin_name_len] = '.';
	out_file[bin_folder_len + bin_name_len + 1] = 'c';
	out_file[bin_folder_len + bin_name_len + 2] = '\0';
	*in = argv[1];
	*out0 = out_file;
	*out1 = bin_file;
}

static inline void compile(char *in, char *out0, char *out1) {
	parse_check(in, out0);
	if (no_gen_exe) {
		return;
	}
	pid_t cpid;
	if (no_exe) {
		cpid = 0;
	} else {
		cpid = fork();
	}
	if (cpid == -1) {
		err(1, "could not fork");
	} else if (cpid == 0) {
		char *(args[]) =
				{ "/bin/gcc", "-shared",
						no_include ? "-I/usr/include/" : "-Iexp/include/", "-o",
						out1,
						generate_obj_file ? "-c" :
						use_static_c_hacker ?
								"-L~/git/C-Hacker/exp/static/libc-hacker.a" :
								"-L~/git/C-Hacker/exp/shared/libc-hacker.so",
						out0, NULL };
		for (char** a = args; *a; a++) {
			fputs(*a, stdout);
			putc(' ', stdout);
		}
		putc('\n', stdout);
		execv("/bin/gcc", args);
	} else {
		fflush(NULL);
		wait_for_normal_exit(cpid);
	}
}

static inline void execute_check(char *check_file) {
	void *check_dl = dlopen(check_file, RTLD_NOW | RTLD_GLOBAL);
	if (!check_dl) {
		fprintf(stderr, "coudl not open the shared object '%s' (%s)",
				check_file, dlerror());
		exit(1);
	}
	void (**cur_check)() = dlsym(check_dl, "checks");
	if (!cur_check) {
		fprintf(stderr,
				"coudl not get the symbol 'checks' of shared object '%s' (%s)",
				check_file, dlerror());
		exit(1);
	}
	for (; *cur_check; cur_check++) {
		puts("execute now a check");
		(*cur_check)();
		puts("executed a check");
	}
	dlclose(check_dl);
}

static inline void wait_for_normal_exit(pid_t pid) {
	while (1) {
		int status;
		waitpid(pid, &status, 0);
		if (WIFCONTINUED(status) || WIFSTOPPED(status)) {
			continue;
		} else if (WIFSIGNALED(status)) {
			fprintf(stderr, "child terminated because of signal %d\n",
					WTERMSIG(status));
		} else if (WIFEXITED(status) && !WEXITSTATUS(status)) {
			return;
		} else if (WIFEXITED(status)) {
			fprintf(stderr, "child terminated with exit code %d\n",
					WEXITSTATUS(status));
		} else {
			fprintf(stderr, "unknown result of waitpid: %d\n", status);
		}
		exit(2);
	}
}

static inline void parse_check(const char *in, const char *out) {
	size_t line_size = 128;
	char *line = malloc(128);
	if (!line) {
		err(1, "could not allocate the line buffer!");
	}
	FILE *in_str = fopen64(in, "r");
	if (!in_str) {
		err(1, "could not open the input stream %s", in);
	}
	FILE *out_str = fopen64(out, "w");
	if (!out_str) {
		err(1, "could not open the output stream %s", out);
	}
	size_t checks_size = 64;
	size_t remain_checks = 4;
	char **checks = malloc(checks_size);
	if (!line) {
		err(1, "could not allocate the checks buffer!");
	}
	fprintf(out_str, "/*\n"
			" * This file is generated by the c-hacker.\n"
			" * original source file: %s\n"
			" */\n", out);
	char **next_check = checks;
	while (1) {
		ssize_t reat = getline(&line, &line_size, in_str);
		if (reat <= 0) {
			if (!reat || !errno) {
				break;
			}
			err(1, "getline");
		}
		if (!strcmp("#include <c-hacker/ignore.h>", line)) {
			continue;
		} else if (starts_with("CHECK ", line)
				|| starts_with("CHECK\t", line)) {
			line += 6;
			size_t len;
			for (len = 0;;) {
				switch (line[len]) {
				case '\n':
				case '(':
					goto loop_end;
				case ' ':
				case '\t':
					if (len == 0) {
						line++;
						continue;
					} else {
						goto loop_end;
					}
				default:
					if (isalpha(line[len]) || line[len] == '_') {
						len++;
						continue;
					} else {
						goto loop_end;
					}
				}
			}
			loop_end: ;
			if (!--remain_checks) {
				remain_checks += 4;
				checks_size += 64;
				checks = realloc(checks, checks_size);
				if (!checks) {
					err(1,
							"could not reallocate enugh memory to remember more checks (%d)! next check: %s",
							checks_size >> 3, line - 6);
				}
				next_check = checks + (checks_size >> 3) + remain_checks;
			}
			*next_check = malloc(len + 1);
			if (!*next_check) {
				err(1,
						"could not allocate enugh memory to remember the check %s!",
						line - 6);
			}
			memcpy(*next_check, line, len);
			(*next_check)[len] = '\0';
			next_check++;
			fputs(func_prefix, out_str);
		}
		fputs(line, out_str);
	}
	fputs("\n\nvoid (*(checks[]))(void) = {", out_str);
	_Bool first = 1;
	for (char **cur_check = checks; cur_check < next_check; cur_check++) {
		if (first) {
			first = 0;
			fprintf(out_str, "\n"
					"\t%s", *cur_check);
		} else {
			fprintf(out_str, ",\n"
					"\t%s", *cur_check);
		}
	}
	if (first) {
		fputs(" ((void (*)(void))0) };\n", out_str);
	} else {
		fputs(",\n"
				"\t((void (*)(void))0)\n" // can't rely on the definition of NULL
				"};\n", out_str);
	}
	fclose(in_str);
	fclose(out_str);
}

static _Bool starts_with(const char *start, const char *string) {
	while (*start == *string) {
		start++;
		string++;
	}
	if (*start) {
		return !*string;
	} else {
		return 1;
	}
}
