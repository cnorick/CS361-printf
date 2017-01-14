#include "printf.hpp"

int printf(const char *fmt, ...){
	char c;
	int len = 0;

	while(c = *fmt++){ // Breaks when '\0' is encountered.
		write(1, &c, 1);
		len++;
	}

    return len;
}



int snprintf(char *dest, size_t size, const char *fmt, ...){
	
}


