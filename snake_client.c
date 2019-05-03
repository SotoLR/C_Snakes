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
	int * applex;
	int * appley;
	int * game_over;
} draw_thread_t;

typedef struct control_thread_struct{
	Snake * player_1;
	Snake * player_2;
} ctrl_thread_t;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void * drawThread(void * args);

int main(int argc, char **argv){
	pthread_t new_tid;

	Snake p1;
	initSnake(&p1, 0);

	Snake p2;
	initSnake(&p2, 1);

	appley = 

	draw_thread_t draw_thread_data;
	draw_thread_data -> player_1 = &p1;
	draw_thread_data -> player_2 = &p2;



	initscr(); //start curses mode
	cbreak(); //disable line buffering
	keypad(stdscr, TRUE);
	noecho();

	pthread_create(&new_tid, NULL, drawThread, &);

	//todo 
	//	init draw thread struct
	//	start draw thread

}

void * drawThread(void * args){
	WINDOW * win;

	refresh(); //refresh curses mode

	//create window
	win = create_newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);

	//get snakes (for easier data extraction)
	Snake * player_1 = (Snake *)((draw_thread_t *)args)->player_1;
	Snake * player_2 = (Snake *)((draw_thread_t *)args)->player_2;

	//set 
	/*int tailx1=0;
	int tailx2=0;
	int taily1=0;
	int taily2=0;
	*/
	int applex, appley;
	while(!*(int *)((draw_thread_t *)args)->game_over){
		//mvaddch(taily1, tailx1, ' ');
		//mvaddch(taily2, tailx2, ' ');
		//todo: draw box and snakes and apple
		/*
		int p1x, p1y, p2x, p2y;
		p1x = player_1->head->x;
		p1y = player_1->head->y;
		p2x = player_2->head->x;
		p2y = player_2->head->y;

		
		switch(player_1->direction){
			case DIR_UP:
				p1y -= SNAKE_SPEED;
			break;
			case DIR_DOWN:
				p1y += SNAKE_SPEED;
			break;
			case DIR_RIGHT:
				p1x += SNAKE_SPEED;
			break;
			case DIR_LEFT:
				p1x -= SNAKE_SPEED;
			break;
		}
		switch(player_2->direction){
			case DIR_UP:
				p2y -= SNAKE_SPEED;
			break;
			case DIR_DOWN:
				p2y += SNAKE_SPEED;
			break;
			case DIR_RIGHT:
				p2x += SNAKE_SPEED;
			break;
			case DIR_LEFT:
				p2x -= SNAKE_SPEED;
			break;
		}
		*/
		win = create_newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);
		
		Point * current = player_1->head;
		for(int i = 0; i < player_1->lenght; i++){
			if(i == (player_1->length-1)){
				mvaddch(current->y, current->x, ' ');
			}else{
				mvaddch(current->y, current->x, player_1->icon);
			}
			current = player_1->head->next;
			if(current = NULL){
				break;
			}
		}
		free(current);
		
		Point * current = player_2->head;
		for(int i = 0; i < player_2->lenght; i++){
		if(i == (player_2->length-1)){
				mvaddch(current->y, current->x, ' ');
			}else{
				mvaddch(current->y, current->x, player_2->icon);
			}
			current = player_2->head->next;
			if(current = NULL){
				break;
			}
		}
		free(current);
		applex = *(int *)((draw_thread_t *)args)->applex;
		appley = *(int *)((draw_thread_t *)args)->appley;
		//mvaddch(, , '@');
		//refresh();
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