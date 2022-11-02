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
	int is_first = 1;
	while (1) {
		signed long s = getline(&line, &size, stdin);
		if (s <= 0) {
			return 0;
		}
		if (*line == '#') {
			continue;
		}
		char c = '\0';
		int weol = 0;
		for (int i = 0; (line[i] != '\n') && (line[i] != '\0'); i++) {
			switch (line[i]) {
			case '{':
			case '(':
				if (c != '\0') {
					putc(line[i], stdout);
					break;
				}
				if (is_first) {
					for (int d = deep; d > 0; d--) {
						putc('\t', stdout);
					}
				}
				is_first = 1;
				deep++;
				putc(line[i], stdout);
				putc('\n', stdout);
				weol = 1;
				break;
			case ')':
			case '}':
				if (c != '\0') {
					putc(line[i], stdout);
					break;
				}
				if (!is_first) {
					putc('\n', stdout);
					is_first = 0;
				}
				deep--;
				for (int d = deep; d > 0; d--) {
					putc('\t', stdout);
				}
				putc(line[i], stdout);
				break;
			case ' ':
			case '\t':
				if (!is_first) {
					putc(line[i], stdout);
				}
				break;
			case '\'':
				if (is_first) {
					is_first = 0;
					for (int d = deep; d > 0; d--) {
						putc('\t', stdout);
					}
				}
				if (c == '\0') {
					c = '\'';
				} else if (c == '\'') {
					c = '\0';
				}
				putc(line[i], stdout);
				break;
			case '"':
				if (is_first) {
					is_first = 0;
					for (int d = deep; d > 0; d--) {
						putc('\t', stdout);
					}
				}
				if (c == '\0') {
					c = '"';
				} else if (c == '"') {
					c = '\0';
				}
				putc(line[i], stdout);
				break;
			case ';':
			case ',':
				if (is_first) {
					for (int d = deep; d > 0; d--) {
						putc('\t', stdout);
					}
				}
				if (c != '\0') {
					putc(line[i], stdout);
					putc('\n', stdout);
					is_first = 1;
					weol = 1;
					break;
				}
				/* no break */
			default:
				if (is_first) {
					for (int d = deep; d > 0; d--) {
						putc('\t', stdout);
					}
				}
				is_first = 0;
				putc(line[i], stdout);
			}
		}
		if (!weol) {
			putc('\n', stdout);
		}
		memset(line, '\0', size);
	}
}

