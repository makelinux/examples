all: tr ansi 99 libc 11 tricks

CFLAGS+=-Wpedantic
CFLAGS+=-Wextra -Wno-missing-field-initializers

tr: CFLAGS+=-std=c89 -Wtraditional
ansi: CFLAGS+=-ansi
99: CFLAGS+=-std=c99
11: CFLAGS+=-std=c11
11: CC=musl-gcc
tricks: CFLAGS+=-g -Og -fsanitize=leak -fno-omit-frame-pointer -Wno-format

check: all
	./tr
	./ansi
	./99
	./libc
	./11
	./tricks
	@echo $@ finished
