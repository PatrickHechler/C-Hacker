/*
 * post-pre-processor.c
 *
 *  Created on: Nov 1, 2022
 *      Author: pat
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char *line = malloc(128);
	size_t size = 128;
	memset(line, '\0', size);
	int deep = 0;
	while (1) {
		signed long s = getline(&line, &size, stdin);
		if (s <= 0) {
			return 0;
		}
		if (*line == '#') {
			continue;
		}
		char c = '\0';
		_Bool weol = 0;
		_Bool is_first = 1;
		for (int i = 0; line[i] != '\n'; i++) {
			switch (line[i]) {
			case '{':
			case '(':
				if (c != '\0') {
					fputc(line[i], stdout);
					break;
				}
				if (is_first) {
					for (int d = deep; d > 0; d--) {
						putc('\t', stdout);
					}
				}
				is_first = 1;
				deep++;
				fputc(line[i], stdout);
				fputc('\n', stdout);
				weol = 1;
				break;
			case ')':
			case '}':
				if (c != '\0') {
					fputc(line[i], stdout);
					break;
				}
				if (!is_first) {
					fputc('\n', stdout);
					is_first = 0;
				}
				deep--;
				for (int d = deep; d > 0; d--) {
					fputc('\t', stdout);
				}
				fputc(line[i], stdout);
				break;
			case ' ':
			case '\t':
				if (!is_first) {
					fputc(line[i], stdout);
				}
				break;
			case '\'':
				if (is_first) {
					is_first = 0;
					for (int d = deep; d > 0; d--) {
						fputc('\t', stdout);
					}
				}
				if (c == '\0') {
					c = '\'';
				} else if (c == '\'') {
					c = '\0';
				}
				fputc(line[i], stdout);
				break;
			case '"':
				if (is_first) {
					is_first = 0;
					for (int d = deep; d > 0; d--) {
						fputc('\t', stdout);
					}
				}
				if (c == '\0') {
					c = '"';
				} else if (c == '"') {
					c = '\0';
				}
				fputc(line[i], stdout);
				break;
			case ';':
			case ',':
				if (is_first) {
					for (int d = deep; d > 0; d--) {
						fputc('\t', stdout);
					}
				}
				if (c != '\0') {
					fputc(line[i], stdout);
					fputc('\n', stdout);
					is_first = 1;
					weol = 1;
					break;
				}
				/* no break */
			default:
				if (is_first) {
					for (int d = deep; d > 0; d--) {
						fputc('\t', stdout);
					}
				}
				is_first = 0;
				fputc(line[i], stdout);
			}
		}
		if (!weol) {
			fputc('\n', stdout);
		}
		memset(line, '\0', size);
	}
}
