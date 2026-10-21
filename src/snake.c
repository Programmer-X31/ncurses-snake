#include "snake.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define X_SPEED 1
#define Y_SPEED 1

struct _node {
	int x;
	int y;
	struct _node *prev;
	struct _node *next;
};

struct _snake {
	WINDOW *window;
	Node *head;
	Node *tail;
	unsigned int len;
	int dx;
	int dy;
	enum Dir dir;
#ifdef DEBUG
	FILE *debug;
#endif
};

/* Add a new node at the head of the snake based on the direction of the snake */
int snake_addHead(Snake *s) {
	if (s == NULL)
		return ERR_ADDHEAD;

	Node *newhead = (Node *) malloc(sizeof(Node));
	if (newhead == NULL)
		return ERR_ADDHEAD;

	if (s->head == NULL) {
		int winwidth, winheight;
		int begx, begy;
		getmaxyx(s->window, winheight, winwidth);
		getbegyx(s->window, begy, begx);
		newhead->x = begx + (winwidth / 2);
		newhead->y = begy + (winheight / 2);

		newhead->prev = NULL;
		newhead->next = NULL;

		s->head = newhead;
		s->tail = newhead;
		s->len = 1;

	} else {
		Node *oldhead = s->head;
		newhead->x = oldhead->x + s->dx;
		newhead->y = oldhead->y + s->dy;

		newhead->prev = NULL;
		newhead->next = oldhead;
		oldhead->prev = newhead;

		s->head = newhead;
		s->len++;
	}
	if (s->window != NULL)
		mvwprintw(s->window, newhead->y, newhead->x, "█");

	return 0;
}

/* Remove the node at the tail of a snake */
int snake_removeTail(Snake *s) {
	if (s == NULL || s->tail == NULL)
		return ERR_REMOVETAIL;

	Node *tmp = s->tail;

	// Erase the tail from the ncurses window.
	if (s->window != NULL)
		mvwprintw(s->window, tmp->y, tmp->x, " ");

	if (s->head == s->tail) {
		// Only one node exists.
		s->head = NULL;
		s->tail = NULL;
		s->len = 0;
	} else {
		// Move the tail backward.
		s->tail = tmp->prev;
		s->tail->next = NULL;

		s->len--;
	}

	free(tmp);
	return 0;
}

/* Initialise Snake pointer and set starting values for the snake */
Snake *snake_init(WINDOW *win) {
	Snake *s = malloc(sizeof *s);

	if (s == NULL)
		return NULL;

	s->window = win;
	s->head = NULL;
	s->tail = NULL;
	s->len = 0;

	/* Set a valid initial direction before calling snake_setDir(). */
	s->dir = RIGHT;
	s->dx = 0;
	s->dy = 0;

	snake_setDir(s, RIGHT);

	if (snake_addHead(s) != 0) {
		free(s);
		return NULL;
	}

#ifdef DEBUG
	s->debug = fopen("debug.log", "a");
#endif

	return s;
}

/* snake_setDir - change direction of snake and prevent opposite direction movements */
void snake_setDir(Snake *s, const enum Dir d) {
	if (abs((d - s->dir)) == 2)
		return;
	switch (d) {
		case UP:
			s->dx = 0;
			s->dy = -Y_SPEED;
			break;
		case DOWN:
			s->dx = 0;
			s->dy = Y_SPEED;
			break;
		case LEFT:
			s->dx = -X_SPEED;
			s->dy = 0;
			break;
		case RIGHT:
			s->dx = X_SPEED;
			s->dy = 0;
			break;
	}
	s->dir = d;
}

/* Store the next location of the snake's head into the pointers given */
void snake_nextLoc(Snake *s, int *y, int *x) {
	if (x == NULL || y == NULL)
		return;
	*y = s->head->y + s->dy;
	*x = s->head->x + s->dx;
}

/* Get the snake's length */
int snake_getLength(Snake *s) { return s->len; }


/* Move the snake and draw it */
int snake_move(Snake *s) {
	int x, y;
	int height, width;
	getmaxyx(s->window, height, width);
	snake_nextLoc(s, &y, &x);
	if (y <= 0 || y >= height - 1 || x <= 0 || x >= width - 1)
		return SNAKEONEDGE;

	int len = s->len;
	snake_addHead(s);
	snake_removeTail(s);
	s->len = len;

#ifdef DEBUG
	snake_printHead(s);
	snake_printTail(s);
#endif
	return 0;
}

/* Delete Snake object */
void snake_destroy(Snake *s) {
	Node *cur = s->head;

	while (cur != NULL) {
		Node *next = cur->next;
		free(cur);
		cur = next;
	}

	s->head = NULL;
	s->tail = NULL;
	s->len = 0;
#ifdef DEBUG
	fclose(s->debug);
#endif

	free(s);
}

#ifdef DEBUG
#include <time.h>

void snake_printTail(Snake *s) {
	time_t now = time(NULL); // Fetches current epoch time

	if (s->tail == NULL) {
		fprintf(s->debug, "[%ld]\tSnake %p\tTail = NULL\n", (long) now, s);
		return;
	}

	fprintf(s->debug, "[%ld]\tSnake %p\tTail = { %d, %d }\n", (long) now, s, s->tail->x, s->tail->y);
}
void snake_printHead(Snake *s) {
	time_t now = time(NULL);
	if (s->tail == NULL) {
		fprintf(s->debug, "[%ld]\tSnake %p\tHead = NULL\n", (long) now, s);
		return;
	}

	fprintf(s->debug, "[%ld]\tSnake %p\tHead = { %d, %d }\n", (long) now, s, s->head->x, s->head->y);
}
#endif
