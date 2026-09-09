#include "libc.h"

void *malloc(size_t size){
    void *ptr = 0;

    HEAP_START = brk(0);

    HEAP_END.size = size;
    HEAP_END.next = NULL;
    HEAP_END.prev = NULL;
    HEAP_END.isFree = 0;


    /*if(HEAP_END != brk(HEAP_END))
        return NULL;*/

    


    return HEAP_START+sizeof(HEAP_END)+size;
}