CFLAGS=-std=c11 -Wall -o shot -lncurses
shot: shot.c
	gcc shot.c $(CFLAGS)
