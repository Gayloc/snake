#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifndef COL
#define COL 10
#endif

#ifndef ROW
#define ROW 32
#endif

#ifndef TIME
#define TIME 500
#endif

struct Point
{
    int x;
    int y;
};

enum Direction
{
    up,
    left,
    down,
    right
};

int get_food_axis(int max);
void food(int map[COL][ROW]);
extern void init(int map[COL][ROW]);
void printMap(int map[COL][ROW]);
extern int start();
void move(int map[COL][ROW]);
int forward(int map[COL][ROW], struct Point *head, enum Direction direction, int *length);
extern void loop(int map[COL][ROW]);

#endif