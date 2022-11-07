/*
 * post-pre-processor.c
 *
 *  Created on: Nov 1, 2022
 *      Author: pat
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	size_t size = 128;
	char *line = malloc(128);
	int deep = 0;
	while (1) {
		size_t reat = getline(&line, &size, stdin);
		if (reat == -1) {
			return EXIT_SUCCESS;
		}
		if (*line == '#') {
			continue;
		}
		int is_first = 1;
		int printed_eol = 0;
		char str = '\0';
		for (long l = 0; line[l] != '\n'; l++) {
			switch (line[l]) {
			case ' ':
			case '\t':
				if (!is_first) {
					goto print;
				}
				break;
			case '}':
				if (str != '\0') {
					goto print;
				}
				deep--;
				if (!is_first) {
					fputc('\n', stdout);
				}
				for (int i = deep; i; i--) {
					fputc('\t', stdout);
				}
				fputc('}', stdout);
				fputc('\n', stdout);
				is_first = 1;
				printed_eol = 1;
				break;
			case '{':
				if (str != '\0') {
					goto print;
				}
				if (is_first) {
					for (int i = deep; i; i--) {
						fputc('\t', stdout);
					}
				}
				deep++;
				fputc('{', stdout);
				fputc('\n', stdout);
				is_first = 1;
				printed_eol = 1;
				break;
			case '\'':
			case '"':
				if (str == line[l]) {
					str = '\0';
				} else if (str == '\0') {
					str = line[l];
				}
				/* no break */
			default:
				if (is_first) {
					is_first = 0;
					for (int i = deep; i; i--) {
						fputc('\t', stdout);
					}
				}
				print: ;
				fputc(line[l], stdout);
				printed_eol = 0;
			}
		}
		if (!printed_eol) {
			fputc('\n', stdout);
		}
	}
	return EXIT_SUCCESS;
}
