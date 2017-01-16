#include "printf.hpp"

int main(){


    int64_t biggestInt = 9223372036854775807;
    int64_t smallestInt = -9223372036854775808;
    int64_t foo = 12;
    int64_t bar = -15;
    char testString[20] = "Woo String!!";


    printf("%x\n", 4560);
    printf("Biggest int in hex: %x\n", biggestInt);
    printf("Biggest int in hex: %x\n", 2147483647);
    printf("foo %%\nThis is a string: %s\n", testString);
    printf("These are ints: %d, %d\nThis is the biggest 64-bit int: %d\nThis is the smallest int: %d\nThis is zero: %d\n", foo, bar, biggestInt, smallestInt, 0);

}

