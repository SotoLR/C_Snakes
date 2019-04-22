#Snakes Makefile
CC = gcc
LIBS = -lncurses
FLAGS = -Wall -g -std=gnu99

CURSESTEST = curses_test
GENERALTEST = gen_test

all: $(CURSESTEST) $(GENERALTEST)

tests: $(CURSESTEST) $(GENERALTEST)

$(CURSESTEST): $(CURSESTEST).c
	$(CC) -o $@.o $< $(FLAGS) $(LIBS)

$(GENERALTEST): $(GENERALTEST).c
	$(CC) -o $@.o $< $(FLAGS) $(LIBS)

clean:
	rm -rf *.o $(TEST)
