#Snakes Makefile
CC = gcc
LIBS = -lncurses -lpthread -lm
FLAGS = -Wall -g -std=gnu99

OBJECTS = snake.o

DEPENDS = snake.h

CURSESTEST = curses_test
GENERALTEST = gen_test

SERVER = snake_server
CLIENT = snake_client

all: $(SERVER) $(CLIENT)

tests: $(CURSESTEST) $(GENERALTEST)

$(SERVER): $(SERVER).c $(OBJECTS)
	$(CC) -o $@ $< snake.c $(FLAGS) $(LIBS)

$(CLIENT): $(CLIENT).c $(OBJECTS)
	$(CC) -o $@ $< snake.c $(FLAGS) $(LIBS)

$(CURSESTEST): $(CURSESTEST).c $(OBJECTS)
	$(CC) -o $@ $< snake.c $(FLAGS) $(LIBS)

$(GENERALTEST): $(GENERALTEST).c $(OBJECTS)
	$(CC) -o $@ $< snake.c $(FLAGS) $(LIBS)

clean:
	rm -rf *.o $(TEST)
	rm -f snake_client
	rm -f snake_server

.PHONY: clean all