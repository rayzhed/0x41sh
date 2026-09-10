SRCS = $(wildcard src/libc/*.c)
LIBC_OBJS = $(patsubst src/libc/%.c, build/src/libc/%.o, $(SRCS))
OBJS = build/crt0.o build/src/main.o $(LIBC_OBJS) $(LIB_OBJS)

LIB_SRCS = $(wildcard src/lib/*.c)
LIB_OBJS = $(patsubst src/lib/%.c, build/src/lib/%.o, $(LIB_SRCS))


0x41sh: $(OBJS)
	ld -e _start -o 0x41sh $(OBJS)

build/crt0.o: crt0.asm
	mkdir -p $(@D)
	nasm -f elf64 crt0.asm -o build/crt0.o

build/src/main.o: src/main.c
	mkdir -p $(@D)
	gcc -c -Wall -Wextra -Iinclude/libc -Iinclude -fno-stack-protector src/main.c -o build/src/main.o

build/src/libc/%.o: src/libc/%.c
	mkdir -p $(@D)
	gcc -c -Wall -Wextra -fno-stack-protector -Iinclude/libc -Iinclude $< -o $@

build/src/lib/%.o: src/lib/%.c
	mkdir -p $(@D)
	gcc -c -Wall -Wextra -fno-stack-protector -Iinclude/libc -Iinclude $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f 0x41sh

re: fclean 0x41sh

.PHONY: clean fclean re
