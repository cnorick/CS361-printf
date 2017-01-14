#include "printf.hpp"

int main(){
    int len = printf("foo %%\nThis is a string: %s\nThis is the biggest 64-bit int: ", "Woo string!", 9223372036854775807);
}
