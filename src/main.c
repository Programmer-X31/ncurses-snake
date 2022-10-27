#include "players.h"
#include <locale.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int t_width;
int t_height;
bool gameRunning;

void rectangle(int y1, int x1, int y2, int x2) {
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void init_game() {
    getmaxyx(curscr, t_height, t_width);
    gameRunning = true;

    s_init();
    f_pickLoc();
}

void draw() {
    while (gameRunning) {
        usleep(75000);
        s_update();
        refresh();
    }

    clear();
    s_endgame();

    rectangle(t_height / 2 - 2, t_width / 2 - 13, t_height / 2 + 5,
              t_width / 2 + 15);
    mvprintw(t_height / 2, t_width / 2 - 3, "Game Over");
    mvprintw(t_height / 2 + 1, t_width / 2 - 2, "Score:%d", score);
    mvprintw(t_height / 2 + 3, t_width / 2 - 9, "Press Any Key to Exit");
    timeout(-1);
    getch();
    endwin();
    printf("-----SNAKE GAME-----\n");
    printf("      Score: %d\n", score);
    printf("--------------------\n");
    exit(0);
}

int main(int argc, char *argv[]) {
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
