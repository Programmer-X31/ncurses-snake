#ifndef NCURSES_SNAKE_SNAKE_H
#define NCURSES_SNAKE_SNAKE_H

#include <ncurses.h>

typedef struct _node Node;
enum Dir { UP, LEFT, DOWN, RIGHT };
typedef struct _snake Snake;

Snake *snake_init(WINDOW *w);
int snake_addHead(Snake *s);
int snake_removeTail(Snake *s);
int snake_getLength(Snake *s);
int snake_move(Snake *s);
void snake_nextLoc(Snake *s, int *y, int *x);
void snake_setDir(Snake *s, const enum Dir d);
void snake_destroy(Snake *s);

#define ERR_ADDHEAD -1
#define ERR_REMOVETAIL -1
#define SNAKEONEDGE -1

#ifdef DEBUG
void snake_printTail(Snake *s);
void snake_printHead(Snake *s);
#endif

#endif // NCURSES_SNAKE_SNAKE_H
