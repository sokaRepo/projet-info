#include <stdio.h>

void red(char* str) {
	printf("\033[0;31m%s\033[0m\n", str);
}

void blue(char* str) {
	printf("\033[0;34m%s\033[0m\n", str);
}