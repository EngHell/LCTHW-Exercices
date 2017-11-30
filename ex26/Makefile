CFLAGS=-std=c11 -Wall -g
CCFLAGS=-c $(CFLAGS)
DEPENDENCIES=config.o


all:
	gcc $(CCFLAGS) $(RCONFIGDEP) config.c -o config.o
	gcc $(CFLAGS) $(DEPENDENCIES) logfind.c -o logfind

clean:
	rm -f logfind
	rm -f readconfig.o
