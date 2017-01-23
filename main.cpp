#include "printf.hpp"

int main(){


    int64_t biggestInt = 9223372036854775807;
    int64_t smallestInt = -9223372036854775808;
    uint64_t biggestUInt = 18446744073709551615;
    int64_t foo = 12;
    int64_t bar = -15;
    char testString[20] = "Woo String!!";
	int len;
	double testDouble = 1234.56789;
	double negDouble = -15.0;

    printf("%x\n", 5678);
    printf("Biggest int in hex: %x\n", biggestInt);
    printf("Biggest uint in hex: %x\n", biggestUInt);
    printf("0 in hex: %x\n", 0);
    printf("-1 in hex: %x\n", -1);
    printf("foo %%\nThis is a string: %s\n", testString);
    printf("These are ints: %d, %d\nThis is the biggest 64-bit int: %d\nThis is the smallest int: %d\nThis is zero: %d\n", foo, bar, biggestInt, smallestInt, 0);
	printf("This is a double: %f\n", testDouble);
	printf("This is a negative double: %f\n", negDouble);
	printf("This is 0.0: %f\n", 0.0);
	printf("9 precision double: %.9f\n", testDouble);
	printf("1 precision double: %.1f\n", testDouble);

	printf("\n");


	char snprintfTest[30];
	len = snprintf(snprintfTest, 30, "0123456789abcdef");
	printf("snprintf string test: %s\n", snprintfTest);
	printf("snprintf len: %d\n\n", len);

	len = snprintf(snprintfTest, 30, "%d", 123456);
	printf("snprintf int test: %s\n", snprintfTest);
	printf("snprintf len: %d\n\n", len);

	len = snprintf(snprintfTest, 30, "%x", 1024);
	printf("snprintf hex test: %s\n", snprintfTest);
	printf("snprintf len: %d\n\n", len);

	len = snprintf(snprintfTest, 30, "%x : %s : %d", 1024, "poop", 1024);
	printf("snprintf multiple param test: %s\n", snprintfTest);
	printf("snprintf len: %d\n\n", len);

	len = snprintf(snprintfTest, 30, "asdfasdflkasjdflaksjdflakdjfalskdfjalskdfjalsdkfalsdkfjalsdkfjalsdkfalskdfalskdfalskdfjalsdkfjalsdkfjalsdkfj END");
	printf("snprintf huge string test: %s\n", snprintfTest);
	printf("snprintf len: %d\n\n", len);
}

