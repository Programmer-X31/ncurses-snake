#ifndef NCURSES_SNAKE_FOOD_H
#define NCURSES_SNAKE_FOOD_H
#include <ncurses.h>

typedef struct {
	WINDOW *window;
	int x;
	int y;
} Food;

Food *food_init(WINDOW *win);
void food_randomLoc(Food *f);
void food_draw(Food *f);
void food_loc(Food *f, int *y, int *x);
void food_destroy(Food *f);


#endif // NCURSES_SNAKE_FOOD_H
