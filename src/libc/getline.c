#include "libc.h"

ssize_t getline(char **lineptr, size_t *n, int fd){

    char *buf = *lineptr;
    char c;
    size_t i = 0;

    while (i < *n -1){
        ssize_t ret = read(fd, &c, 1);
        if (ret <= 0)
            break;
        
        buf[i] = c;
        i++;

        if (c == '\n')
            break;
        
    }

    buf[i] = '\0';
    return i;
}