#include "libc.h"

ssize_t write(int fd, const void *str, size_t len) {
    long ret;
    __asm__ volatile (
        "mov %1, %%rdi\n"   // fd
        "mov %2, %%rsi\n"   // str
        "mov %3, %%rdx\n"   // len
        "mov $1, %%rax\n"   // write
        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd), "r"(str), "r"(len)
        : "rdi", "rsi", "rdx"
    );
    return ret;
}

/*int main(int argc, char **argv, char **envp) {
    const char msg[] = "Hello World!\n";
    ssize_t ret = write(1, msg, sizeof(msg) - 1);
    if (ret < 0) {
        // We got an error
        return 1;
    }
    return 0;
}*/