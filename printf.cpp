#include "printf.hpp"
#define NULL nullptr

#define MAX_ARRAY_SIZE 30 // This is the biggest char array we need to hold any of the converted strings.

int getConvertedValue(char type, va_list args, char * const output);
char *strcopy(char *destination, const char *source);
void RemovePadding(char *&hexdigits);

int printf(const char *fmt, ...){
	char c;
	int len = 0;
	char valueString[MAX_ARRAY_SIZE];

	va_list args;
	va_start(args, fmt);

	while((c = *fmt++)){ // Breaks when '\0' is encountered.
		char *chptr = valueString;
		if(c == '%'){
			if(getConvertedValue(*fmt++, args, chptr) == -1)
				return -1; // printf doc says return negative on failure.
			while((c = *chptr++)){
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
	char backwardsString[MAX_ARRAY_SIZE];
	int i = 0, j = 0;

	// Convert input to positive if it is negative.
	// The smallest negative when multiplied by -1 is larger than the largest positive,
	// so we have to account for that in the if block.
	if(input < 0){
		input++;
		input *= -1;
		output[j++] = '-';

		backwardsString[i++] = (char) ('0' + (input % 10) + 1); // input % 10 is the least significant digit.
		input /= 10;
	}

	do{

		backwardsString[i++] = (char) ('0' + input % 10); // input % 10 is the least significant digit.

	} while((input /= 10) != 0);
	i--;

	// Reversing the string for output.
	while(i >= 0)
		output[j++] = backwardsString[i--];

	output[j++] = '\0';

	return 0;
}

int intToHex(uint64_t input, char * const output){
    char asciiforhex[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    char hexdigits[17];
    char *chptr = hexdigits;
    size_t getnibble = 0x0000000f;
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

void RemovePadding(char *&hexdigits){
    //remove leading zeros loop stops when it reaches a nonzero or there is one character left
    //this is so that 0 is represented 
    for(int i = 0; i < 15; i++){
        if(*hexdigits == '0') hexdigits++;
        else break;
    }
    return;    
}

// Loads sign, exponent, and fraction with the appropriate values from input.
void getDoubleParts(int64_t input, bool *positive, int64_t *exponent, int64_t *fraction){
    *positive = (input & (0x1ll << 63)) == 0;
    *exponent = (input & (0x7ffll << 63)) >> 52; // exponent is located in range [52,62].
    *fraction = input & 0xfffffffffffffll;
}

int doubleToString(double input, char * const output){
    bool positive;
    int64_t exponent, fraction;

    getDoubleParts((int64_t)input, &positive, &exponent, &fraction);
    printf("is positive: %d\n", positive);
    printf("exponent part: %d\n", exponent);
    return 0;
}


int snprintf(char *dest, size_t size, const char *fmt, ...){
    return 0;
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
	while((*destination++ = *source++)){}

	return destination;
}
