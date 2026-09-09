#include "libc.h"

int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    while (i < n && *s1 == *s2 && *s1 != '\0'){
        s1++;
        s2++;
        i++;
    }
    if (i == n)
        return 0;
    return *s1 - *s2;
}