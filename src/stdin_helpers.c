#include "stdin_helpers.h"

#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFERSIZE (20)

// safely read integer from stdin
int get_int_from_stdin(void) {
	char input_buffer[INPUT_BUFFERSIZE] = {0};
	fgets(input_buffer, INPUT_BUFFERSIZE, stdin);
	int output = strtol(input_buffer, NULL, 10);
	return output;
}

// safely read unsigned integer from stdin
unsigned get_uint_from_stdin(void) {
	char input_buffer[INPUT_BUFFERSIZE] = {0};
	fgets(input_buffer, INPUT_BUFFERSIZE, stdin);
	unsigned output = strtoul(input_buffer, NULL, 10);
	return output;
}

// safely read size_t from stdin
size_t get_sizet_from_stdin(void) {
	char input_buffer[INPUT_BUFFERSIZE] = {0};
	fgets(input_buffer, INPUT_BUFFERSIZE, stdin);
	size_t output;
	sscanf(input_buffer, "%zu", &output);
    return output;
}

// safely read double from stdin
double get_double_from_stdin(void) {
	char input_buffer[INPUT_BUFFERSIZE] = {0};
	fgets(input_buffer, INPUT_BUFFERSIZE, stdin);
	double output = strtod(input_buffer, NULL);
	return output;
}