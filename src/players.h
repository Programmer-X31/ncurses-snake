#ifndef __CHARACTER_H_
#define __CHARACTER_H_
#include <stdbool.h>

struct pos {
	int x;
	int y;
};


static int t_width = 100;
static int t_height = 20;
static bool gameRunning = true;

void s_init(int width, int height);
void s_setLimits(int width, int height);
void s_changePos();
void s_setDir(int x, int y);
void s_eat(int x, int y);
void s_update();

void f_pickLoc();
struct pos f_getLoc();

#endif
