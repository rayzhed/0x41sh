/* prototypes et types de ma mini libc */
#ifndef LIBC_H
#define LIBC_H

#define NULL ((void *)0)

typedef unsigned long long size_t;
typedef long long ssize_t;

struct header {
    size_t size;
    struct header *next;
    struct header *prev;
    int isFree;
};
typedef struct header t_header;

extern void * HEAP_START;
extern void * HEAP_END;


ssize_t write(int fd, const void *buf, size_t count);

int putchar(char c);

int puts(const char *str);

int putnbr(int num);

int puthex(unsigned long num);

int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, size_t n);

ssize_t read(int fd, void *buf, size_t count);

ssize_t getline(char **lineptr, size_t *n, int fd);

[[noreturn]] void exit(int status);

int printf(const char *format, ...);

void *brk(void *addr);

void *sbrk(int size);

void *malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void *memcpy(void *dest, const void *src, size_t n);

#endif