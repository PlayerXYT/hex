
#include "common.h"

void convert(FILE* input_file, FILE* output_file) {
	char buf[1024], hex[2048];
	size_t len = fread(buf, sizeof(char), 1024, input_file);
	while(len) {
		char tmp;
		for(uint i=0;i<len;i++) {
			tmp = (char)((buf[i]&240)/16);
			if(tmp<10)
				hex[i*2] = tmp+48;
			else
				hex[i*2] = tmp+55;
			tmp = buf[i]&15;
			if(tmp<10)
				hex[i*2+1] = tmp+48;
			else
				hex[i*2+1] = tmp+55;
		}

		fwrite(hex, sizeof(char), len*2, output_file);
		fflush(output_file);
		len = fread(buf, sizeof(char), 1024, input_file);
	}
}

void explain_command() {
		printf("\e[0;7mhex\e[0m converts binary data to raw hex data\nUsage: \e[7mhex [input] [output]\e[0m\ninput is either a file or \e[1mSTDIN\e[0m\noutput is either a file, \e[1mSTDOUT\e[0m, \e[1mSTDERR\e[0m or blank for a .hex file\n\e[93mWarning:\e[0m If output is ommitted, input must not be STDIN\n\ne.g. \e[7mhex data.bin\e[0m will read from data.bin and write to data.bin.hex\n");
}

FILE* generate_output(FILE* input_file, const char* input_file_name) {
	char output_file_name[strlen(input_file_name)+4];
	strcpy(output_file_name, input_file_name);
	strcat(output_file_name, ".hex");
	return fopen(output_file_name, "w");
}
