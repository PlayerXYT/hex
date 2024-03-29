
#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define uint unsigned int

// Provided by common
void die(int code);

// Must be provided to common
void convert(FILE* input_file, FILE* output_file);
void explain_command();
FILE* generate_output(FILE* input_file, const char* input_file_name);
