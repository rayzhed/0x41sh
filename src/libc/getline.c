#include "libc.h"

ssize_t getline(char **lineptr, size_t *n, int fd){

    char *buf = *lineptr;
    char c;
    size_t i = 0;

    if (*n == 0)
        return -1;

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

    /*ligne trop longue pour le buffer : on jette la fin, sinon elle revient
      au tour d'apres comme si c'etait une commande*/
    if (i > 0 && buf[i - 1] != '\n'){
        while (read(fd, &c, 1) > 0 && c != '\n')
            ;
    }

    return i;
}