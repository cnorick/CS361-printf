#include "printf.hpp"

int main(){

  printf("%x\n", 4560);
  
	int64_t biggestInt = 9223372036854775807;
	int64_t smallestInt = -9223372036854775808;
	int64_t foo = 12;
	int64_t bar = -15;
	char testString[20] = "Woo String!!";
    int len = printf("foo %%\nThis is a string: %s\nThese are ints: %d, %d\nThis is the biggest 64-bit int: %d\nThis is the smallest int: %d\nThis is zero: %d\n", testString, foo, bar, biggestInt, smallestInt, 0);

	//int64_t i = 0;
	//while(true)
		//printf("%d\n", i++);
		
//	printf("%d", 0);


}

