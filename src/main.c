#include <ncurses.h>
#include <stdlib.h>
#include "players.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <locale.h>


void draw()
{
	while(gameRunning)
	{
		usleep(75000);
		s_update();
		refresh();
	}

}

int main(int argc, char *argv[])
{
	int w, h;
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	curs_set(0);
	timeout(1);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
	getmaxyx(curscr, h, w);

	f_pickLoc();
	s_init(w, h);
	draw();

	endwin();
}
