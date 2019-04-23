#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#include "snake.h"

#define WIN_HEIGHT 30
#define WIN_WIDTH 50

typedef struct thread_data_struct{
	Snake * player_1;
	//Snake * player_2;
	//connection_info_here
} thread_data_t;

int main(int argc, char **argv){

	int x = 10;
	int y = 10;
	char icon = '#';
	dir = DIR_RIGHT;

	initscr(); //start curses mode
	cbreak(); //disable line buffering
	keypad(stdscr, TRUE);
	noecho();

}

