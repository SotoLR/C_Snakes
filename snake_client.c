#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

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
} draw_thread_t;

typedef struct control_thread_struct{
	Snake * player_1;
	Snake * player_2;
} ctrl_thread_t;

void drawGame(draw_thread_t * args);
void * controlThread(void * args);

int game_over;

int main(int argc, char **argv){
	pthread_t new_tid;

	Snake * p1 = malloc(sizeof(Snake));
	initSnake(p1, 0);

	Snake * p2 = malloc(sizeof(Snake));
	initSnake(p2, 1);


	int ay = 5;
	int ax = 5;

	draw_thread_t draw_thread_data;
	draw_thread_data.player_1 = p1;
	draw_thread_data.player_2 = p2;
	draw_thread_data.applex = &ax;
	draw_thread_data.appley = &ay;

	ctrl_thread_t ctrl_thread_data;
	ctrl_thread_data.player_1 = p1;
	ctrl_thread_data.player_2 = p2;
	
	game_over = 0;

	initscr(); //start curses mode
	cbreak(); //disable line buffering
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	
	pthread_create(&new_tid, NULL, controlThread, &ctrl_thread_data);
	drawGame(&draw_thread_data);

	//todo 
	//	init draw thread struct
	//	start draw thread

	endwin();

}

void drawGame(draw_thread_t * args){
	WINDOW * win;

	refresh(); //refresh curses mode

	win = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);
	box(win, 0, 0);
	wrefresh(win);

	//mvaddch(WIN_Y+1, WIN_X+1, '+');

	//get snakes (for easier data extraction)
	Snake * player_1 = (Snake *)args->player_1;
	Snake * player_2 = (Snake *)args->player_2;

	int applex, appley;
	int x, y;

	while(!game_over){
		usleep(100000);
		//win = create_newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);
		
		x = player_1->head->x;
		y = player_1->head->y;

		//printf("%d\n",player_1->direction);
		//mvaddch(WIN_Y+5, WIN_X+5, (char)player_1->direction);

		switch(player_1->direction){
			case DIR_LEFT:
				x--;
			break;
			case DIR_RIGHT:
				x++;
			break;
			case DIR_UP:
				y--;
			break;
			case DIR_DOWN:
				y++;
			break;
		}
		push_front(player_1, 0, x, y);

		wrefresh(win);

		Point * current1 = player_1->head;
		for(int i = 0; i < player_1->length; i++){
			if(i == (player_1->length-1)){
				mvaddch(current1->y, current1->x, ' ');
			}else{
				mvaddch(current1->y, current1->x, player_1->icon);
			}
			current1 = player_1->head->next;
			if(current1 == NULL){
				break;
			}
		}
		//free(current1);
		
		Point * current2 = player_2->head;
		for(int i = 0; i < player_2->length; i++){
		if(i == (player_2->length-1)){
				mvaddch(current2->y, current2->x, ' ');
			}else{
				mvaddch(current2->y, current2->x, player_2->icon);
			}
			current2 = player_2->head->next;
			if(current2 == NULL){
				break;
			}
		}
		//free(current2);
		applex = *(int *)args->applex;
		appley = *(int *)args->appley;
		mvaddch(appley, applex, '@');
		refresh();
	}

}

void * controlThread(void * args){
	Snake * player_1 = (Snake *)((ctrl_thread_t *)args)->player_1;
	//Snake * player_2 = (Snake *)((ctrl_thread_t *)args)->player_2;

	int ch;

	player_1->direction = DIR_RIGHT;
	//player_2->direction = DIR_LEFT;

	while(!game_over){
		ch = getch();
		//timeout(100);
		

		switch(ch){
			case KEY_LEFT:
				player_1->direction = DIR_LEFT;
			break;
			case KEY_RIGHT:
				player_1->direction = DIR_RIGHT;
			break;
			case KEY_UP:
				player_1->direction = DIR_UP;
			break;
			case KEY_DOWN:
				player_1->direction = DIR_DOWN;
			break;
		}

		if(player_1->head->x < (WIN_X) || player_1->head->x > (WIN_X+WIN_WIDTH-1) || player_1->head->y < (WIN_Y) || player_1->head->y > (WIN_Y+WIN_HEIGHT-1)){
			game_over = 1;
		}
	}

	return NULL;
}