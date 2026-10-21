#ifndef NCURSES_SNAKE_SNAKE_H
#define NCURSES_SNAKE_SNAKE_H

#include <ncurses.h>

typedef struct _node Node;
enum Dir { UP, LEFT, DOWN, RIGHT };
typedef struct _snake Snake;

Snake *snake_init(WINDOW *w);
int snake_addHead(Snake *s);
int snake_removeTail(Snake *s);
int snake_getScore(Snake *s);
void snake_nextLoc(Snake *s, int *y, int *x);
void snake_move(Snake *s);
void snake_setDir(Snake *s, const enum Dir d);
void snake_destroy(Snake *s);
void snake_grow(Snake *s);

void snake_printTail(Snake *s);
void snake_printHead(Snake *s);

#endif // NCURSES_SNAKE_SNAKE_H
