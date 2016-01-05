CC=gcc
CFLAGS=-Wall -Werror

FILES=$(shell ls *.c)

essai_pile: $(patsubst %.c, %.o, $(FILES))
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

essai_pile.o: pile.h pile_io.h
pile.o: pile.h
pile_io.o: pile_io.h pile.h
