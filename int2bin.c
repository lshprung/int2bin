#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//globals
int bits = 32;
bool raw = false;

void print_help(char *name){
	printf("Usage: %s [OPTION]... NUMBER...\n", name);
	printf("Convert NUMBER(S) to binary\n\n");

	printf("Options:\n");
	printf("  -b, --bits NUM \tSpecify number of bits to print (default is 32)\n");
	printf("  -h, --help     \tPrint this help message and exit\n");
	printf("      --raw      \tPrint only the binary form\n");
}

char *to_bin(int n, int bits){
	char *out = malloc(sizeof(char) * (bits+1));
	bool negative = false; //keep track of whether n is negative (and requires 2s compliment notation)
	int i;

	out[bits] = '\0';

	//handle negative numbers
	if(n < 0){
		n = -1 * (n + 1);
		negative = true;
	}

	for(i = bits-1; i >= 0; --i){
		out[i] = (n & 1 ? '1' : '0');
		n = n >> 1;
	}

	//if negative, flip the bits
	if(negative){
		for(i = 0; i < bits; ++i){
			out[i] = 48 + ((out[i] - 47) % 2);
		}
	}

	return out;
}


int main(int argc, char **argv){
	int i;

	//print help if no arguments
	if(argc < 2){
		print_help(argv[0]);
		return 0;
	}

	//check for arguments
	for(i = 1; i < argc; ++i){
		if(!(strcmp(argv[i], "--"))){
			++i;
			break;
		}
		else if(!(strcmp(argv[i], "-b")) || !(strcmp(argv[i], "--bits"))){
			if(i+1 >= argc) break; //check that the flag was given an argument
			bits = atoi(argv[i+1]);
			++i;
		}
		else if(!(strcmp(argv[i], "-h")) || !(strcmp(argv[i], "--help"))) print_help(argv[0]);
		else if(!(strcmp(argv[i], "--raw"))) raw = true;
		else break;
	}

	//convert each argument to binary
	while(i < argc){
		if(!raw) printf("%d -> ", atoi(argv[i]));
		printf("%s\n", to_bin(atoi(argv[i]), bits));
		++i;
	}
}
