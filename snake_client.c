#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>

#include "snake.h"

#define CLIENT_MSG_LEN 4
#define SERVER_MSG_LEN 32
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

typedef struct receive_data_struct{
	int * status;
	int * new_p1x;
	int * new_p1y;
	int * p1_grow_flag;
	int * new_p2x;
	int * new_p2y;
	int * p2_grow_flag;
	int * applex
	int * appley;
} received_t;

//void drawGame(draw_thread_t * args);
void drawGame();
void * controlThread(void * args);

int game_over;
int latest_input;
int player_number;

int main(int argc, char **argv){
	pthread_t new_tid;

	//draw_thread_t draw_thread_data;
	//INIT DRAW THREAD DATA?

	ctrl_thread_t ctrl_thread_data; //change this?
	ctrl_thread_data.player_1 = p1;
	ctrl_thread_data.player_2 = p2;
	
	game_over = 0;

	char msg_get[SERVER_MSG_LEN];
	int connection_fd = connectSocket(argv[1], argv[2]);
	char msg_send[CLIENT_MSG_LEN];
	sprintf(msg_send, "%d %d", 0, 0); //what is this send for? Is it necessary?

	int status;
	int new_p1x, new_p1y, p1_grow_flag;
	int new_p2x, new_p2y, p2_grow_flag;
		
	printf("Waiting for opponent...");
	while(1){
		printf(".");
		recvString(connection_fd, msg_get, SERVER_MSG_LEN);
		sscanf(msg_get, "%d %d %d %d %d %d %d %d %d",
			&status,
			&new_p1x, &new_p1y, &p1_grow_flag,
			&new_p2x, &new_p2y, &p2_grow_flag,
			&applex, &appley);
		if(status == 0){
			continue;
		}else if(status == 1){
			//set me as player 1
			printf("You are player 1 -> #######\n");
			player_number = 1;
			usleep(TIMEOUT_MILIS*1000*50);
			break;
		}else if(status == 2){
			//set me as player 2
			printf("You are player 2 -> &&&&&&&\n");
			player_number = 2;
			usleep(TIMEOUT_MILIS*1000*50);
			break;
		}else{
			printf("Something's wrong...");
			break;
		}
	}
	
	initscr(); //start curses mode
	cbreak(); //disable line buffering
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	
	
	pthread_create(&new_tid, NULL, controlThread, &ctrl_thread_data);
	drawGame(connection_fd);
	//drawGame(&draw_thread_data);

	endwin();
}

//void drawGame(draw_thread_t * args){
void drawGame(int connection_fd){
	WINDOW * win;

	refresh(); //refresh curses mode

	int win_x = (LINES - height)/2;
	int win_y = (COLS - width)/2;

	win = newwin(WIN_HEIGHT, WIN_WIDTH, win_y, win_x);
	box(win, 0, 0);
	wrefresh(win);

	//mvaddch(WIN_Y+1, WIN_X+1, '+');

	Snake * player_1 = malloc(sizeof(Snake));
	initSnake(player_1, 0);

	Snake * player_2 = malloc(sizeof(Snake));
	initSnake(player_2, 1);

	//int applex, appley; //to be received
	//int nx1, ny1, nx2, ny2; //to be received

	int status;
	int new_p1x, new_p1y, p1_grow_flag;
	int new_p2x, new_p2y, p2_grow_flag;

	char msg_get[SERVER_MSG_LEN];
	char msg_send[CLIENT_MSG_LEN];

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
		recvString(connection_fd, msg_get, SERVER_MSG_LEN);
		sscanf(msg_get, "%d %d %d %d %d %d %d %d %d",
			status,
			new_p1x,
			new_p1y,
			p1_grow_flag,
			new_p2x,
			new_p2y,
			p2_grow_flag,
			applex,
			appley);

		if(*new_msg->status == 1){
			game_over = 1;
		}

		push_front(player_1, p1_grow_flag, win_x + 1 + new_p1x, win_y + 1 + new_p1y);
		push_front(player_2, p2_grow_flag, win_x + 1 + new_p1x, win_y + 1 + new_p2x);
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
		mvaddch(win_y + 1 + appley, win_x + 1 + applex, '@');
		refresh();

		sprintf(msg_send, "%d %d", player_number, latest_input);
		sendString(connection_fd, msg_send, CLIENT_MSG_LEN);
	}
	switch(status){
		case 4:
			//you win
		break;
		case 5:
			//you lose
		break;
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