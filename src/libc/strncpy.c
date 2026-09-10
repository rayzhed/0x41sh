#include "libc.h"

/* Coucou, oublie pas que on rajoute \0 à la fin donc écris jusqu'à n+1 :} */
char *strncpy(char *dest, const char *src, size_t n){
    size_t i = 0;
    while (i < n && (src[i] != '\0')){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return dest;
}