#ifndef __CHARACTER_H_
#define __CHARACTER_H_
#include <ncurses.h>
#include <stdbool.h>

struct pos {
    int x;
    int y;
};

extern int score;        // snake.c
extern struct pos f_pos; // food.c
extern int t_width;      // main.c
extern int t_height;     // main.c
extern bool gameRunning; // main.c

void s_init();
void s_setLimits(int width, int height);
void s_changePos();
void s_setDir(int x, int y);
void s_eat(int x, int y);
void s_update();
void s_endgame();

void f_pickLoc();
struct pos f_getLoc();

extern void rectangle(int y1, int x1, int y2, int x2);
#endif
