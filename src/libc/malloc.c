#include "libc.h"

void * HEAP_START;
void * HEAP_END;

void *malloc(size_t size){

    size=(size+15) & ~15;

    if (HEAP_START != NULL){
    t_header *current = (t_header *)HEAP_START;

        while (current != NULL){
            if (current->isFree == 1 && size <= current->size){

                if (current->size > size + sizeof(t_header) + 16){
                    void *newChunk = (char *)current + sizeof(t_header) + size;
                    t_header *newHeader = (t_header *)newChunk;

                    newHeader->size=current->size-(size+sizeof(t_header));
                    newHeader->isFree=1;
                    newHeader->prev=current;
                    newHeader->next=current->next;
                    
                    current->next=newHeader;

                    if (newHeader->next != NULL)
                        newHeader->next->prev = newHeader;
                }

                current->isFree=0;
                current->size=size;
                return (char *)current + sizeof(t_header);
            }
            current = current->next;
        }
    }


    void *chunk = sbrk(sizeof(t_header) + size); 

    if (chunk == (void *)-1)
        return NULL;

        
    t_header *h = (t_header *)chunk;

    h->size=size;
    h->next=NULL;
    h->prev=NULL;
    h->isFree=0;
    
    if (HEAP_START == NULL){
        HEAP_START = chunk;
    }else{
        t_header *current = (t_header *)HEAP_START;

        while (current->next != NULL){
            current = current->next;
        }
        current->next = h;
        h->prev = current;
    }

    return (char *)chunk+sizeof(t_header);
}