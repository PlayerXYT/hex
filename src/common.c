
#include "common.h"

void die(int code) {
	if(code)
		printf("\e[0;91mExited with exit code \e[1m%d\e[0m\n", code);
	exit(code);
}

void main(int argc, char** argv) {
	// Check if arguments are specified or --help is passed
	if(argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
		explain_command();
		die(1);
	}

	FILE* input_file;
	FILE* output_file;

	// Find input file
	if(!strcmp(argv[1], "STDIN"))
		input_file = stdin;
	else {
		input_file = fopen(argv[1], "r");
		if(!input_file) {
			printf("\e[0;1;91mError:\e[0m Could not open input file or file does not exist!\n");
			die(1);
		}
	}

	// Find output file
	if(argc == 2)
		output_file = generate_output(input_file, argv[1]);
	else if(!strcmp(argv[2], "STDOUT"))
		output_file = stdout;
	else if(!strcmp(argv[2], "STDERR"))
		output_file = stderr;
	else {
		output_file = fopen(argv[2], "w");
		if(!output_file) {
			printf("\e[0;1;91mError:\e[0m Could not open output file!\n");
			fclose(input_file);
			die(1);
		}
	}

	// Convert file, clean up and exit
	convert(input_file, output_file);
	fclose(input_file);
	fflush(output_file);
	fclose(output_file);
	die(0);
}
