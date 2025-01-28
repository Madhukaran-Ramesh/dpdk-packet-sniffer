CC = gcc
CFLAGS = -O3 -march=native -I/usr/local/include/dpdk
LDFLAGS = -L/usr/local/lib -lrte_eal -lrte_ethdev -lrte_mbuf

all: main

main: src/main.c
    $(CC) $(CFLAGS) -o main src/main.c $(LDFLAGS)

clean:
    rm -f main
