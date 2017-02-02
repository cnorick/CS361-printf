#include "printf.hpp"
#define NULL nullptr

#define MAX_ARRAY_SIZE 10000 // This is the biggest char array we need to hold any of the converted strings.

int _snprintf(char *dest, size_t size, const char *fmt, va_list args);
int getConvertedValue(char type, va_list args, char * const output, int precision);
char *strcopy(char *destination, const char *source);
void RemovePadding(char *&hexdigits);

int printf(const char *fmt, ...){
	char valueString[MAX_ARRAY_SIZE];

	va_list args;
	va_start(args, fmt);

	int len = _snprintf(valueString, MAX_ARRAY_SIZE, fmt, args);

	write(1, valueString, len);

	va_end(args);

	return len;
}

int snprintf(char *dest, size_t size, const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	
	int len = _snprintf(dest, size, fmt, args);

	va_end(args);

	return len;
}

// Internal version of _snprintf that does most of the work for printf and snprintf.
int _snprintf(char *dest, size_t size, const char *fmt, va_list args) {
	char valueString[MAX_ARRAY_SIZE];
	char c;
	int len = 0; // The length of the string returned by getConvertedValue.
	int precision = 6;

	// Parse through format string one character at a time.
	while((c = *fmt++)) { // Breaks when '\0' is encountered.
		char *chptr = valueString;

		if(c == '%'){
			if(*fmt == '.') {
				fmt++;
				precision = *fmt++ - '0';
			}

			if(getConvertedValue(*fmt++, args, chptr, precision) == -1)
				return -1; // snprintf doc says return negative on failure.

			while((c = *chptr++)){
				if(++len < size - 1) // -1 to account for null char.
					dest[len - 1] = c;
			}
		}

		else if(++len < size - 1)
			dest[len - 1] = c;
	}

	dest[len < size ? len : size] = '\0'; // Put the null char at the smallest of len and size.

	return len;
}

// Converts an int64_t to a string and stores the string in output.
// Function assumes that ouput is large enough to hold the generated
// string. Appends a null character to output before returning.
// Function returns 0 upon success.
int intToString(int64_t input, char * const output){
	char backwardsString[MAX_ARRAY_SIZE];
	char *outputptr = output;
    int i = 0, j = 0;
    
    if(input < 0) *outputptr++ = '-';;
    while(input != 0){
        backwardsString[i] = '0' + input % 10;
        input /= 10;
        if(input != 0) i++;
    }
    while(i >= 0){
        *outputptr++ = backwardsString[i--];
    }
    *outputptr = '\0';

    return 0;
}

// Converts a uint64_t to a string and stores the string in output.
// Function assumes that ouput is large enough to hold the generated
// string. Appens a null character to output before returning.
// Function retunrs a 0 upon success.
int intToHex(uint64_t input, char * const output){
	char asciiforhex[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	char hexdigits[17];
	char *chptr = hexdigits;
	size_t getnibble = 0xf;
	size_t index;


	//use bit arithmetic to find the hex digit for each nibble then place the hex character into the array
	for(int i = 15; i > -1; i--){
		index = input & getnibble;
		hexdigits[i] = asciiforhex[index >> ((15-i)*4)];
		getnibble = getnibble << 4;    
	}    

	hexdigits[16] = '\0';
	RemovePadding(chptr); //remove leading 0s

	//place the hex representation into the output array in the format 0x...
	output[0] = '0';
	output[1] = 'x';

	for(int i = 0; i < 17; i++){
		output[2+i] = *(chptr+i);
		if(*(chptr+i) == '\0') break;
	}

	return 0;
}

// Converts a double to a string having <precision> characters to the right
// of the decimal place, and stores the string in output.
// Function assumes that output is large enough to hold the generated
// string. Appens a null character to output before returning.
// Function retunrs a 0 upon success.
int doubleToString(double input, char * const output, int precision){
	int intPart;
	double fractionPart;
        double rounder;
	char intString[MAX_ARRAY_SIZE];
	char fractionString[MAX_ARRAY_SIZE];
	char *outputIterator = output;

	// Take care of negatives.
	if(input < 0) {
		*outputIterator++ = '-';
		input *= -1;
	}
	
	intPart = (int) input; // Truncates off everything on the right of the decimal.
	fractionPart = input - intPart; // Everything on the right of the decimal.

        //Shift the rounder to one more than the precision of the double
	rounder = 5.5;
        for(int i = 0; i < precision + 1; i++)
		rounder /= 10;


	//This operation will effectively round the double
        fractionPart += rounder;
    

	// Get the int part.
	intToString(intPart, intString);

        //Get the fractional part
        for(int i = 0; i < precision; i++){
            fractionPart *= 10;
            fractionString[i] = '0' + (int64_t) fractionPart % 10;
            fractionString[i+1] = '\0';
        }

        //copy the integer string to the output array
	strcopy(outputIterator, intString);

	// Iterate output to the null char following the int part.
	while(*++outputIterator);

	// Then replace the '\0' with a '.' and add the rounded fraction part to the end of the string.
	*outputIterator++ = '.';

        //copy the fraction string to the output
	strcopy(outputIterator, fractionString);

	return 0;
}


// Takes the type (d,x,f,s,%) as provided in the format string, and the va_list of
// args accompanying the format string. Based on the type, it stores in output a c string
// (ends with '\0') representation of the next arg in args. Returns -1 on invalid type.
int getConvertedValue(char type, va_list args, char * const output, int precision){
	switch(type){
		case 'd':
			return intToString(va_arg(args, int64_t), output);
		case 'x':
			return intToHex(va_arg(args, uint64_t), output);
		case 'f':
			return doubleToString(va_arg(args, double), output, precision);
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

// Removes leading 0's from hex string.
void RemovePadding(char *&hexdigits){
	//remove leading zeros loop stops when it reaches a nonzero or there is one character left
	//this is so that 0 is represented 
	for(int i = 0; i < 15; i++){
		if(*hexdigits == '0') hexdigits++;
		else break;
	}
	return;    
}

// Copies the c string from source to destination. Returns destination.
char *strcopy(char *destination, const char *source){
	while((*destination++ = *source++)){}

	return destination;
}
