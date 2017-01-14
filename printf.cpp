#include "printf.hpp"
#define NULL nullptr

#define MAX_ARRAY_SIZE 30 // This is the biggest char array we need to hold any of the converted strings.

int getConvertedValue(char type, va_list args, char * const output);
char *strcopy(char *destination, const char *source);

int printf(const char *fmt, ...){
	char c;
	int len = 0;
	char valueString[MAX_ARRAY_SIZE];
	char * chptr = valueString;

	va_list args;
	va_start(args, fmt);

	while(c = *fmt++){ // Breaks when '\0' is encountered.
		if(c == '%'){
			if(getConvertedValue(*fmt++, args, chptr) == -1)
				return -1; // printf doc says return negative on failure.
			while(c = *chptr++){
				write(1, &c, 1);
				len++;
			}
		}
		else{
			write(1, &c, 1);
			len++;
		}
	}

	va_end(args);

	return len;
}


int intToString(int64_t input, char * const output){
	char backwardsString[100];

//	do{
//		int temp = input % 10; // Gets the least significant digit.


//	} while((input /= 10) != 0);

}
int intToHex(uint64_t input, char * const output){

}

int doubleToString(double input, char * const output){

}


int snprintf(char *dest, size_t size, const char *fmt, ...){

}

// Takes the type (d,x,f,s) as provided in the format string, and the va_list of
// args accompyaning the format string. Based on the type, it stores in output a c string
// (ends with '\0') representation of the next arg in args. Returns null on invalid type.
int getConvertedValue(char type, va_list args, char * const output){
	switch(type){
		case 'd':
			return intToString(va_arg(args, int64_t), output);
		case 'x':
			return intToHex(va_arg(args, uint64_t), output);
		case 'f':
			return doubleToString(va_arg(args, double), output);
		case 's':
			strcopy(output, va_arg(args, char*));
			return 0;
		case '%':
			output[0] = '%';
			output[1] = '\0';
			return 0;
		default:
			return -1;
	}
}

// Copies the c string from source to destination. Returns destination.
char *strcopy(char *destination, const char *source){
	while(*destination++ = *source++){}

	return destination;
}
