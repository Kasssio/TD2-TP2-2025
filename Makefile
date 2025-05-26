CC=c99
CFLAGS=-Wall -Wextra -pedantic -O0 -ggdb
LIBS=-lm
all: main.out bestPathCheck.out

main.out: utils.c main.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

bestPathCheck.out: utils.c bestPathCheck.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean
clean:
	rm -f *.o *.out
