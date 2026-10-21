#include <locale.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "food.h"
#include "snake.h"

static bool gameRunning;

#define GAMEWIN_HEIGHT 31
#define GAMEWIN_WIDTH 101

#define SCOREWIN_HEIGHT 5
#define SCOREWIN_WIDTH 35

int main() {
	gameRunning = true;

	setlocale(LC_ALL, "");

	initscr();
	noecho();
	curs_set(0);
	timeout(1);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);

	WINDOW *game_win = newwin(GAMEWIN_HEIGHT, GAMEWIN_WIDTH, 1, 5);
	WINDOW *score_win = newwin(SCOREWIN_HEIGHT, SCOREWIN_WIDTH, GAMEWIN_HEIGHT + 4, 5 + (GAMEWIN_WIDTH / 2) - 35 / 2);

	if (game_win == NULL) {
		endwin();
		return 1;
	}
	box(game_win, 0, 0);
	box(score_win, 0, 0);

	Snake *s = snake_init(game_win);
	Food *f = food_init(game_win);
	int ch;
	int snake_x, snake_y;
	int food_x, food_y;

	food_draw(f);

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

		snake_nextLoc(s, &snake_y, &snake_x);
		food_loc(f, &food_y, &food_x);
		if (snake_x == food_x && snake_y == food_y) {
			snake_addHead(s);
			food_randomLoc(f);
			food_draw(f);
		}
		if (snake_move(s) == SNAKEONEDGE)
			gameRunning = false;

		mvwprintw(score_win, 2, 5, "Score: %d", snake_getLength(s));

		// Update game logic/render frame
		usleep(80000);
		refresh(); // Refresh screen
		wrefresh(game_win); // Refresh game window
		wrefresh(score_win); // Refresh score window
	}

	timeout(-1);

	// Cleanup code
	snake_destroy(s);
	food_destroy(f);
	delwin(game_win);
	delwin(score_win);
	endwin();
	exit(0);
}
