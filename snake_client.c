#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <netdb.h>
#include <arpa/inet.h>

#include "snake.h"

/*
typedef struct thread_data_struct{
	Snake * player_1;
	Snake * player_2;
	//connection_info_here
} thread_data_t;
*/

typedef struct draw_thread_struct{
	Snake * player_1;
	Snake * player_2;
	int * game_over;
} draw_thread_t;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void * drawThread(void * args);

int main(int argc, char **argv){

	int x = 10;
	int y = 10;
	//char icon = '#';
	dir = DIR_RIGHT;

	initscr(); //start curses mode
	cbreak(); //disable line buffering
	keypad(stdscr, TRUE);
	noecho();

	//todo 
	//	init draw thread struct
	//	start draw thread

}

void * drawThread(void * args){
	WINDOW * win;

	refresh();
	win = create_newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);

	Snake * player_1 = (Snake *)((draw_thread_t *)args)->player_1;
	Snake * player_2 = (Snake *)((draw_thread_t *)args)->player_2;

	Point * current = player_1->head;
	for(int i = 0; i < player_1->lenght; i++){
		mvaddch(current->y, current->x, player_1->icon);
		current = player_1->head->next;
		if(current = NULL){
			break;
		}
	}

	Point * current = player_2->head;
	for(int i = 0; i < player_2->lenght; i++){
		mvaddch(current->y, current->x, player_2->icon);
		current = player_2->head->next;
		if(current = NULL){
			break;
		}
	}

	while(!*(int *)((draw_thread_t *)args)->game_over){
		//todo: draw box and snakes
		switch(player_1->direction){

		}
		switch(player_2->direction){
			
		}
		win = create_newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);

	}

}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}