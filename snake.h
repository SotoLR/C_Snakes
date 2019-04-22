#ifndef SNAKE_LIB_GUARD
#define SNAKE_LIB_GUARD

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_RIGHT 2
#define DIR_LEFT 3

typedef struct point_struct{
	int x;
	int y;
	struct point_struct * next;
} Point;

typedef struct snake_struct{
	Point * head;
	int length;
} Snake;

void makePoint(Point* p, int x, int y); //sets point at given addr
Point newPoint(int x, int y); //Creates new point (assign this to a new var)
void push_front(Snake * snk, int flag, int x, int y); //add to front of snake, if flag, last is not deleted
int push_back(Snake * snk, int x, int y); //add to back of snake, return new length
Point * rm_last(Snake * s);
void printSnake(Snake * snk);

#endif