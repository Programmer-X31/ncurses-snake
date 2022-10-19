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
		usleep(50000);
		s_update();
		refresh();
	}

}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	int w, h;
	initscr();
	noecho();
	curs_set(0);
	timeout(1);
	getmaxyx(curscr, h, w);

	s_init(w, h);
	draw();

	endwin();
}
