#include "food.h"
#include <locale.h>
#include <stdlib.h>
#include <time.h>


/* Initialise food sprite inside a window. Returns NULL on failure */
Food *food_init(WINDOW *win) {
	Food *f = (Food *) malloc(sizeof(Food));

	if (f == NULL)
		return NULL;

	f->window = win;
	food_randomLoc(f);

	return f;
}

/* Set a randow location to a food sprite given */
void food_randomLoc(Food *f) {
	srand((unsigned) time(NULL));

	f->x = 1 + ((rand() % (getmaxx(f->window) - 1)));
	f->y = 1 + ((rand() % (getmaxy(f->window) - 1)));
}

/* Store current food location to the pointers passed */
void food_loc(Food *f, int *y, int *x) {
	*y = f->y;
	*x = f->x;
}

/* Draw the food sprite */
void food_draw(Food *f) {
	// mvprintw(f->pt.y, f->pt.x, "█");
	attron(COLOR_PAIR(1));
	mvwaddch(f->window, f->y, f->x, 'f');
}

/* Delete a food sprite from memory */
void food_destroy(Food *f) { free(f); }
