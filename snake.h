#ifndef SNAKE_LIB_GUARD
#define SNAKE_LIB_GUARD

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_RIGHT 2
#define DIR_LEFT 3

#define STANDARD_SNAKE_LENGTH 4
#define SNAKE_SPEED 1

#define WIN_HEIGHT 20
#define WIN_WIDTH 50
#define WIN_X 10
#define WIN_Y 1

#define STATUS_WAIT 0
#define STATUS_P1 1
#define STATUS_P2 2
#define STATUS_NONE 3
#define STATUS_WIN 4
#define STATUS_LOSE 5

#define TIMEOUT_MILIS 100

typedef struct point_struct{
	int x;
	int y;
	struct point_struct * next;
} Point;

typedef struct snake_struct{
	Point * head;
	int length;
	int direction;
	char icon;
} Snake;

void makePoint(Point* p, int x, int y); //sets point at given addr
Point * newPoint(int x, int y); //Creates new point (assign this to a new var)
Point * push_front(Snake * s, int flag, int x, int y); //add to front of snake, if flag, last is not deleted
int push_back(Snake * snk, int x, int y); //add to back of snake, return new length
Point * rm_last(Snake * s);
void printSnake(Snake * snk);
void initSnake(Snake * snk, int player_num); //initialize snake values based on player number
#endif