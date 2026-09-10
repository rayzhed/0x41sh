#include "libc.h"

size_t strlen(const char *s)
{
    size_t n = 0;
    while (*s != '\0') {
        n++;
        s++;
    }
    return n;
}