#include "libc.h"

void * brk(void *addr){
    ssize_t ret;
    __asm__ volatile (
        "mov %1, %%rdi\n"   // brk
        "mov $12, %%rax\n"   // addr

        "syscall\n"
        : "=a"(ret)
        : "r"(addr)
        : "rdi"
    );
    return (void *)ret;
}