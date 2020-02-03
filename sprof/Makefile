all: libdemo.so.1.0.1 prog

CFLAGS+=-g
libdemo.so.1.0.1: libdemo.c

libdemo.so.1.0.1:
	cc -g -fPIC -shared -Wl,-soname,libdemo.so.1 -o $@ $^
	ln -sf libdemo.so.1.0.1 libdemo.so.1
	ln -sf libdemo.so.1 libdemo.so

CFAGS=-g
prog: LDLIBS=-L. -ldemo

