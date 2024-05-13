CC=zig-linux-x86_64-0.12.0/zig cc
CFLAGS=-Wall -g

life: life.o
zig-install:
	curl -qL https://ziglang.org/download/0.12.0/zig-linux-x86_64-0.12.0.tar.xz | tar Jx
clean:
	rm -rf *.o life
.PHONY: zig-install clean
