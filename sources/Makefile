CC=gcc
CFLAGS=-Wall -Werror

FILES=$(shell ls *.c)

projet: $(patsubst %.c, %.o, $(FILES))
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

