#include "libc.h"

int open(const char *filename, int flags, umode_t mode){
    int ret;
    __asm__ volatile (
        "mov %1, %%rdi\n"   // filename
        "mov %2, %%rsi\n"   // flags
        "mov %3, %%rdx\n"   // mode
        "mov $2, %%rax\n"   // open

        "syscall\n"
        : "=a"(ret)
        : "r"(filename), "r"((long)flags), "r"((long)mode)
        : "rdi", "rsi", "rdx"
    );
    return ret;
}