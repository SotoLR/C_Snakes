#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

//sets point at given addr
void makePoint(Point* p, int x_val, int y_val){
	p -> x = x_val;
	p -> y = y_val;
	p -> next = NULL;
}

//Creates new point (assign this to a new var)
Point * newPoint(int x_val, int y_val){
	Point * p = malloc(sizeof(Point));
	p->x = x_val;
	p->y = y_val;
	p->next = NULL;
	return p;
}

//return new length
int push_back(Snake * snk, int x, int y){
	int i=0;

	Point * first = snk -> head;
	Point * new_point = malloc(sizeof(Point));
	makePoint(new_point, x, y);

	while(first->next != NULL){
		++i;
		first = first -> next;
	}

	first -> next = new_point;

	return i+2;
}

Point * push_front(Snake * s, int flag, int x, int y){
	Point * new_point = malloc(sizeof(Point));
	Point * removed;
	makePoint(new_point, x, y);

	new_point -> next = s -> head;
	s -> head = new_point;

	if(flag){
		s->length++;
	}else{
		removed = rm_last(s);
		return removed;
	}
	return NULL;
}

Point * rm_last(Snake * s){
	int i;
	Point * tail = s -> head;
	Point * temp;
	for(i=1; i < s->length; i++){
		tail = tail -> next;
	}
	temp = tail -> next;
	tail -> next = NULL;
	return temp;
}

void printSnake(Snake * snk){
	Point * first = snk -> head;
	while(first->next != NULL){
		printf("%d:%d ", first->x, first->y);
		first = first->next;
	}
	printf("%d:%d ", first->x, first->y);
	printf("\n");
}

void initSnake(Snake * snk, int player){
	int start_x, start_y, grow_dir;
	if(player == 0){
		start_x = WIN_X+STANDARD_SNAKE_LENGTH + 1;
		grow_dir = -1;
		start_y = WIN_Y+2;
		snk->icon = '#';
	}else{
		start_x = WIN_X + WIN_WIDTH - STANDARD_SNAKE_LENGTH - 1;
		grow_dir = 1;
		start_y = WIN_Y + WIN_HEIGHT - 3;
		snk->icon = '&';
	}

	Point * n_head = newPoint(start_x, start_y);
	snk->head = n_head;

	for(int i = 0; i < STANDARD_SNAKE_LENGTH; i++){
		start_x += grow_dir;
		push_back(snk, start_x, start_y);
	}
	
	snk->length = STANDARD_SNAKE_LENGTH;
	
	if(player == 0){
		snk->direction = DIR_RIGHT;
	}else{
		snk->direction = DIR_LEFT;
	}
}