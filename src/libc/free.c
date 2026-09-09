#include "libc.h"
void free(void *ptr){

    if (ptr == NULL){
        return;
    }

    void *addr = (char *)ptr-sizeof(t_header);
    t_header *chunk = (t_header *)addr;

    chunk->isFree = 1;

    if(chunk->next != NULL && chunk->next->isFree == 1)
    {
        t_header *n = chunk->next;

        chunk->size=chunk->size+n->size+sizeof(t_header);
        chunk->next = n->next;
        if(chunk->next != NULL)
            chunk->next->prev=chunk;
    }

    if(chunk->prev != NULL && chunk->prev->isFree == 1)
    {
        t_header *p = chunk->prev;

        p->size = p->size + chunk->size + sizeof(t_header);
        p->next = chunk->next;
        if (p->next != NULL)
            p->next->prev = p;
    }
}