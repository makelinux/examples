all: tr ansi 99 libc

CFLAGS+=-Wpedantic
CFLAGS+=-Wextra -Wno-missing-field-initializers

tr: CFLAGS+=-std=c89 -Wtraditional
ansi: CFLAGS+=-ansi
99: CFLAGS+=-std=c99
