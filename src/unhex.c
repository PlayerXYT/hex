
#include "common.h"

void convert(FILE* input_file, FILE* output_file) {
	char buf[2048], hex[1024];
	size_t len = fread(buf, sizeof(char), 2048, input_file);
	while(len) {
		size_t out_len = (size_t)(len/2);
		for(uint i=0;i<out_len;i++) {
			buf[i*2] -= 48;
			if(buf[i*2] > 9)
				buf[i*2] -= 7;
			buf[i*2+1] -= 48;
			if(buf[i*2+1] > 9)
				buf[i*2+1] -= 7;
			hex[i] = buf[i*2]*16 + buf[i*2+1];
		}

		fwrite(hex, sizeof(char), out_len, output_file);
		fflush(output_file);
		len = fread(buf, sizeof(char), 2048, input_file);
	}
}

void explain_command() {
		printf("\e[0;7munhex\e[0m converts raw hex data to binary data\nUsage: \e[7munhex [input] [output]\e[0m\ninput is either a file or \e[1mSTDIN\e[0m\noutput is either a file, \e[1mSTDOUT\e[0m, \e[1mSTDERR\e[0m or blank\n\e[93mWarning:\e[0m If output is omitted, input must end with .hex\n\ne.g. \e[7munhex data.bin.hex\e[0m will read from data.bin.hex and write to data.bin\n");
}

FILE* generate_output(FILE* input_file, const char* input_file_name) {
	if(strlen(input_file_name) < 5 || strcmp(input_file_name+strlen(input_file_name)-4, ".hex")) {
		printf("\e[0;1;91mError:\e[0m File name must end with .hex if output is not specified\n");
		fclose(input_file);
		die(1);
	}
	char output_file_name[strlen(input_file_name)];
	strcpy(output_file_name, input_file_name);
	output_file_name[strlen(output_file_name)-4] = 0;
	return fopen(output_file_name, "w");
}
