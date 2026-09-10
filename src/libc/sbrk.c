#include "libc.h"

void * sbrk(int size){

    void * v = brk (0);

    void * vSize = (char *)v+size;

    void * ret = brk(vSize);

    // some debug printf("v=%p vSize=%p ret=%p\n", v, vSize, ret);

    if(ret != vSize)
        return (void *)-1;

   return v;
}