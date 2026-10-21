#include "snake.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define HEIGHT 31
#define WIDTH 101

int main(void) {
	bool gameRunning = true;

	setlocale(LC_ALL, "");

	initscr();
	noecho();
	curs_set(0);
	timeout(1);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);

	WINDOW *game_win = newwin(HEIGHT, WIDTH, 1, 5);
	// WINDOW *score_win = newwin(5, 35, 1, 5);

	if (game_win == NULL) {
		endwin();
		return 1;
	}
	box(game_win, 0, 0);
	// box(score_win, 0, 0);


	Snake *s = snake_init(NULL);
	int ch;
	int snake_x, snake_y;

	while (gameRunning) {
		if ((ch = getch()) != ERR) {
			switch (ch) {
				case 'w':
				case 'W':
					snake_setDir(s, UP);
					break;
				case 'a':
				case 'A':
					snake_setDir(s, LEFT);
					break;
				case 's':
				case 'S':
					snake_setDir(s, DOWN);
					break;
				case 'd':
				case 'D':
					snake_setDir(s, RIGHT);
					break;
				case 'q':
				case 'Q':
					gameRunning = false;
					break;
			}
		}

		snake_move(s);

		snake_loc(s, &snake_y, &snake_x);

		snake_printTail(s);
		snake_printHead(s);

		snake_move(s);
		// mvwprintw(score_win, 2, 5, "Score: %d", snake_getScore(s));
		// Update game logic / render frame
		usleep(80000);
		// refresh();
		// wrefresh(game_win);
		// wrefresh(score_win);
	}


	// timeout(-1);

	snake_destroy(s);
	delwin(game_win);
	// delwin(score_win);
	endwin();
	exit(0);
}
