#include "snake.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define X_SPEED 1
#define Y_SPEED 1

#define ERR_ADDHEAD -1
#define ERR_REMOVETAIL -1

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

int snake_removeTail(Snake *s) {
	// Remove the node at the tail of a snake
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

		// The new tail must not point to the removed node.
		s->tail->next = NULL;

		s->len--;
	}

	free(tmp);
	return 0;
}

Snake *snake_init(WINDOW *win) {
	Snake *s = (Snake *) malloc(sizeof(Snake));

	if (s == NULL)
		return NULL;

	s->window = win;
	snake_setDir(s, RIGHT);
	snake_addHead(s);
	return s;
}

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

void snake_nextLoc(Snake *s, int *y, int *x) {
	*y = s->head->y + s->dy;
	*x = s->head->x + s->dx;
}

void snake_grow(Snake *s) {
	s->len++;
	if (s->window != NULL)
		// for (Node *tmp = s->head; tmp != NULL; tmp = tmp->next)
		mvwprintw(s->window, s->tail->y, s->tail->x, "█");
}
int snake_getScore(Snake *s) { return s->len; }

void snake_move(Snake *s) {
	// int len = s->len;
	// Add a node to the head of the Snake (rear of the queue)
	snake_addHead(s);
	snake_printHead(s);

	// Remove an element from the tail of the snake (front of the queue)
	snake_removeTail(s);
	snake_printTail(s);

	// s->len = len;
}

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
	free(s);
}

#include <time.h>
FILE *fp;
time_t now; // Fetches current epoch time
void snake_printTail(Snake *s) {
	now = time(NULL); // Fetches current epoch time

	fp = fopen("debug.log", "a");
	if (s->tail == NULL) {
		fprintf(fp, "[%ld]\tSnake %p\tTail = NULL\n", (long) now, s);
		return;
	}

	fprintf(fp, "[%ld]\tSnake %p\tTail = { %d, %d }\n", (long) now, s, s->tail->x, s->tail->y);

	fclose(fp);
}
void snake_printHead(Snake *s) {
	fp = fopen("debug.log", "a");
	now = time(NULL);
	if (s->tail == NULL) {
		fprintf(fp, "[%ld]\tSnake %p\tHead = NULL\n", (long) now, s);
		return;
	}

	fprintf(fp, "[%ld]\tSnake %p\tHead = { %d, %d }\n", (long) now, s, s->head->x, s->head->y);
	fclose(fp);
}
