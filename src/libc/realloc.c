#include "libc.h"

void *realloc(void *ptr, size_t size)
{

    if (ptr == NULL)
        return malloc(size);
    
    if (size == 0){
        free(ptr);
        return NULL;
    }

    t_header *h = (t_header *)((char *)ptr - sizeof(t_header));
    if (size <= h->size)
        return ptr;
    
    void *n = malloc(size);
    if (n == NULL)
        return NULL;
    
    memcpy(n, ptr, h->size);
    free(ptr);
    return n;
}