kdir := /home/luc/gh/WSL2-Linux-Kernel
inc_dir := $(kdir)/tools/lib
lib_dir := $(kdir)/tools/lib/bpf

CFLAGS += -I$(inc_dir)
LDFLAGS += -L$(lib_dir) -lbpf

CC = clang

all: loader kill.o

loader: load.c
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

kill.o: kill.c
	$(CC) -target bpf -D __BPF_TRACING__ -I$(inc_dir) \
		-Wall -Werror -O2 -c -g $< -o $@

.PHONY: all clean

clean:
	rm -f loader
	rm -f *.o
