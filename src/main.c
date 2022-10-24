#include <ncurses.h>
#include <stdlib.h>
#include "players.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <locale.h>


int t_width;
int t_height;
bool gameRunning;

void init_game()
{
	getmaxyx(curscr, t_height, t_width);
	gameRunning = true;

	s_init();
	f_pickLoc();
}

void draw()
{
	while(gameRunning)
	{
		usleep(75000);
		s_update();
		refresh();
	}
	clear();
	mvprintw(t_height/2, t_width/2-4, " Game Over ");
	mvprintw(t_height/2 + 1, t_width/2-9, "Press Any Key to Exit");
	timeout(-1);
	getch();
	endwin();
	printf("\n-----SNAKE GAME-----\n");
	printf("Score: %d\n", score);
	exit(0);

	


}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	initscr();
	noecho();
	curs_set(0);
	timeout(1);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

	init_game();
	draw();

	endwin();
}
