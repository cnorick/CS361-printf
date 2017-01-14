#include "printf.hpp"

int printf(const char *fmt, ...){
    write(1, "foo", 3);

    return 1;
}
