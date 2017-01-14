#include "printf.hpp"

#define NULL nullptr

char* getConvertedValue(char type, va_list args);

int printf(const char *fmt, ...){
	char c;
	int len = 0;
	char *valueString;

	va_list args;
	va_start(args, fmt);

	while(c = *fmt++){ // Breaks when '\0' is encountered.
		if(c == '%'){
			if(!(valueString = getConvertedValue(*fmt++, args)))
				return -1; // printf doc says return negative on failure.
			while(c = *valueString++){
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



int snprintf(char *dest, size_t size, const char *fmt, ...){
	
}

// Takes the type (d,x,f,s) as provided in the format string, and the va_list of
// args accompyaning the format string. Based on the type, it returns a c string
// (ends with '\0') representation of the next arg in args. Returns null on invalid type.
char* getConvertedValue(char type, va_list args){
	switch(type){
		case 'd':
			break;
		case 'x':
			break;
		case 'f':
			break;
		case 's':
			return va_arg(args, char*);
		case '%':
			return "%";
		default:
			return NULL;
	}
}
