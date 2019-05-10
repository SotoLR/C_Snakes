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

/*
typedef struct draw_thread_struct{
	Snake * player_1;
	Snake * player_2;
	int * applex;
	int * appley;
} draw_thread_t;
*/

typedef struct control_thread_struct{
	Snake * player_1;
	Snake * player_2;
} ctrl_thread_t;

//void drawGame(draw_thread_t * args);
void drawGame(draw_thread_t * args);
void * controlThread(void * args);

int game_over;
int latest_input;

int main(int argc, char **argv){
	pthread_t new_tid;

	//draw_thread_t draw_thread_data;
	//INIT DRAW THREAD DATA?

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
	drawGame();
	drawGame(&draw_thread_data);

	endwin();
}

//void drawGame(draw_thread_t * args){
void drawGame(){
	WINDOW * win;

	refresh(); //refresh curses mode

	win = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);
	box(win, 0, 0);
	wrefresh(win);

	//mvaddch(WIN_Y+1, WIN_X+1, '+');

	Snake * player_1 = malloc(sizeof(Snake));
	initSnake(player_1, 0);

	Snake * player_2 = malloc(sizeof(Snake));
	initSnake(player_2, 1);

	int applex, appley; //to be received
	int nx1, ny1, nx2, ny2; //to be received

	while(!game_over){
		//usleep(TIMEOUT_MILIS*1000);
		//win = create_newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);
		
		//x = player_1->head->x;
		//y = player_1->head->y;

		//printf("%d\n",player_1->direction);
		//mvaddch(WIN_Y+5, WIN_X+5, (char)player_1->direction);

		/*
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
		*/
		

		push_front(player_1, 0, x, y);

		wrefresh(win);

		//printf("p1\n");
		Point * current1 = player_1->head;
		for(int i = 0; i < player_1->length; i++){
			//printw("x %d y %d\n", current1->x, current1->y);
			if(i == (player_1->length-1)){
				mvaddch(current1->y, current1->x, ' ');
			}else{
				mvaddch(current1->y, current1->x, player_1->icon);
			}
			current1 = current1->next;
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
			current2 = current2->next;
			if(current2 == NULL){
				break;
			}
		}
		//free(current2);
		applex = ;
		appley = ;
		mvaddch(appley, applex, '@');
		refresh();
	}

}

void * controlThread(void * args){ //adapt this to SEND

	int ch;

	while(!game_over){
		ch = getch();
		switch(ch){
			case KEY_LEFT:
				latest_input = DIR_LEFT;
			break;
			case KEY_RIGHT:
				latest_input = DIR_RIGHT;
			break;
			case KEY_UP:
				latest_input = DIR_UP;
			break;
			case KEY_DOWN:
				latest_input = DIR_DOWN;
			break;
		}
	}

	return NULL;
}