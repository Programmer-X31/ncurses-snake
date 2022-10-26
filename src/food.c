#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "players.h"

struct pos f_pos;

void f_pickLoc()
{
	time_t t1;
	srand((unsigned) time (&t1));
	f_pos.x = rand() % t_width;
	f_pos.y = rand() % t_height;
	attron(COLOR_PAIR(1));
	mvprintw(f_pos.y, f_pos.x,  "█");
}

