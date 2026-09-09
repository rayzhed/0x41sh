#include "libc.h"

ssize_t read(int fd, void *buf, size_t count){
    long ret;
    __asm__ volatile (
        "mov $0, %%rax\n"   // syscall: read
        "mov %1, %%rdi\n"   // fd
        "mov %2, %%rsi\n"   // buf
        "mov %3, %%rdx\n"   // count
        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd), "r"(buf), "r"(count)
        : "rdi", "rsi", "rdx"
    );
    return ret;
}