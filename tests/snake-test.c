
#include "snake.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TESTS 32

static WINDOW *gamewin;
static WINDOW *statuswin;

struct TestResult {
	const char *name;
	bool passed;
};

static struct TestResult results[MAX_TESTS];
static int test_count = 0;
static int current_test = 0;

static void report_test(const char *name, bool passed) {
	if (test_count >= MAX_TESTS)
		return;

	results[test_count].name = name;
	results[test_count].passed = passed;
	test_count++;

	werase(statuswin);
	mvwprintw(statuswin, 0, 1, "Snake unit tests");
	mvwprintw(statuswin, 1, 1, "[%s] %s", passed ? "PASS" : "FAIL", name);
	mvwprintw(statuswin, 2, 1, "Completed: %d", test_count);
	wrefresh(statuswin);

	current_test++;
}

static Snake *new_test_snake(void) {
	Snake *s = snake_init(gamewin);

	if (s != NULL)
		wrefresh(gamewin);

	return s;
}

/* 1. Initialization creates a valid one-node snake. */
static bool test_init(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	bool passed = snake_getLength(s) == 1;

	int y, x;
	snake_nextLoc(s, &y, &x);

	/* Initial direction is RIGHT. */
	int height, width;
	getmaxyx(gamewin, height, width);

	passed = passed && x == width / 2 + 1 && y == height / 2;

	snake_destroy(s);
	return passed;
}

/* 2. Adding a head increases the length by one. */
static bool test_add_head(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	int result = snake_addHead(s);
	bool passed = result == 0 && snake_getLength(s) == 2;

	snake_destroy(s);
	return passed;
}

/* 3. Removing the tail decreases the length by one. */
static bool test_remove_tail(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	snake_addHead(s);
	int result = snake_removeTail(s);

	bool passed = result == 0 && snake_getLength(s) == 1;

	snake_destroy(s);
	return passed;
}

/* 4. Removing the only node leaves an empty snake. */
static bool test_remove_last_node(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	int result = snake_removeTail(s);

	bool passed = result == 0 && snake_getLength(s) == 0;

	snake_destroy(s);
	return passed;
}

/* 5. Removing a tail from an empty snake returns an error. */
static bool test_remove_empty_tail(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	snake_removeTail(s);

	bool passed = snake_removeTail(s) != 0;

	snake_destroy(s);
	return passed;
}

/* 6. RIGHT direction produces the correct next position. */
static bool test_direction_right(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	snake_setDir(s, RIGHT);

	int y, x;
	snake_nextLoc(s, &y, &x);

	int height, width;
	getmaxyx(gamewin, height, width);

	bool passed = x == width / 2 + 1 && y == height / 2;

	snake_destroy(s);
	return passed;
}

/* 7. UP direction changes the next position correctly. */
static bool test_direction_up(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	snake_setDir(s, UP);

	int y, x;
	snake_nextLoc(s, &y, &x);

	int height, width;
	getmaxyx(gamewin, height, width);

	bool passed = x == width / 2 && y == height / 2 - 1;

	snake_destroy(s);
	return passed;
}

/* 8. DOWN direction changes the next position correctly. */
static bool test_direction_down(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	snake_setDir(s, DOWN);

	int y, x;
	snake_nextLoc(s, &y, &x);

	int height, width;
	getmaxyx(gamewin, height, width);

	bool passed = x == width / 2 && y == height / 2 + 1;

	snake_destroy(s);
	return passed;
}

/* 9. LEFT direction changes the next position correctly. */
static bool test_direction_left(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	/* First change direction so LEFT is not a reversal. */
	snake_setDir(s, UP);
	snake_setDir(s, LEFT);

	int y, x;
	snake_nextLoc(s, &y, &x);

	int height, width;
	getmaxyx(gamewin, height, width);

	bool passed = x == width / 2 - 1 && y == height / 2;

	snake_destroy(s);
	return passed;
}

/* 10. Direct reversal is rejected. */
static bool test_reject_reverse(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	snake_setDir(s, LEFT); /* RIGHT -> LEFT must be rejected. */

	int y, x;
	snake_nextLoc(s, &y, &x);

	int height, width;
	getmaxyx(gamewin, height, width);

	bool passed = x == width / 2 + 1 && y == height / 2;

	snake_destroy(s);
	return passed;
}

/* 11. Growing increases the reported score. */
static bool test_grow(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	int before = snake_getLength(s);
	snake_grow(s);

	bool passed = snake_getLength(s) == before + 1;

	snake_destroy(s);
	return passed;
}

/* 12. Moving keeps the snake's reported length unchanged. */
static bool test_move_length(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	int before = snake_getLength(s);
	snake_move(s);

	bool passed = snake_getLength(s) == before;

	snake_destroy(s);
	return passed;
}

/* 13. Moving advances the next position by one cell. */
static bool test_move_position(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	int y_before, x_before;
	int y_after, x_after;

	snake_nextLoc(s, &y_before, &x_before);
	snake_move(s);
	snake_nextLoc(s, &y_after, &x_after);

	bool passed = x_after == x_before + 1 && y_after == y_before;

	snake_destroy(s);
	return passed;
}

/* 14. The snake can be destroyed after normal operations. */
static bool test_destroy(void) {
	Snake *s = new_test_snake();

	if (s == NULL)
		return false;

	snake_addHead(s);
	snake_move(s);
	snake_destroy(s);

	/* Do not dereference s after destruction. */
	return true;
}

static void run_test(const char *name, bool (*test_fn)(void)) {
	werase(gamewin);
	box(gamewin, 0, 0);
	mvwprintw(gamewin, 1, 2, "Running: %s", name);
	wrefresh(gamewin);

	bool passed = test_fn();
	report_test(name, passed);
}

int main(void) {
	if (initscr() == NULL)
		return EXIT_FAILURE;

	if (LINES < 10 || COLS < 30) {
		endwin();
		fprintf(stderr, "Terminal must be at least 30 columns x 10 rows.\n");
		return EXIT_FAILURE;
	}

	cbreak();
	noecho();
	curs_set(0);

	gamewin = newwin(LINES - 4, COLS, 0, 0);
	statuswin = newwin(4, COLS, LINES - 4, 0);

	if (gamewin == NULL || statuswin == NULL) {
		if (gamewin != NULL)
			delwin(gamewin);
		if (statuswin != NULL)
			delwin(statuswin);

		endwin();
		fprintf(stderr, "Failed to create ncurses windows.\n");
		return EXIT_FAILURE;
	}

	keypad(statuswin, TRUE);
	box(gamewin, 0, 0);
	wrefresh(gamewin);

	run_test("Initialization", test_init);
	run_test("Add head", test_add_head);
	run_test("Remove tail", test_remove_tail);
	run_test("Remove last node", test_remove_last_node);
	run_test("Reject removal from empty snake", test_remove_empty_tail);
	run_test("Direction RIGHT", test_direction_right);
	run_test("Direction UP", test_direction_up);
	run_test("Direction DOWN", test_direction_down);
	run_test("Direction LEFT", test_direction_left);
	run_test("Reject reverse direction", test_reject_reverse);
	run_test("Grow snake", test_grow);
	run_test("Move preserves length", test_move_length);
	run_test("Move advances position", test_move_position);
	run_test("Destroy snake", test_destroy);

	werase(gamewin);
	box(gamewin, 0, 0);
	mvwprintw(gamewin, 1, 2, "Test run complete.");
	wrefresh(gamewin);

	int passed = 0;
	for (int i = 0; i < test_count; i++) {
		if (results[i].passed)
			passed++;
	}

	werase(statuswin);
	mvwprintw(statuswin, 0, 1, "RESULTS: %d/%d passed", passed, test_count);
	mvwprintw(statuswin, 1, 1, "Press any key to exit.");
	wrefresh(statuswin);

	wgetch(statuswin);

	delwin(gamewin);
	delwin(statuswin);
	endwin();

	/* Print a persistent report after leaving ncurses mode. */
	for (int i = 0; i < test_count; i++) {
		printf("[%s] %s\n", results[i].passed ? "PASS" : "FAIL", results[i].name);
	}

	printf("\n%d/%d tests passed.\n", passed, test_count);

	return passed == test_count ? EXIT_SUCCESS : EXIT_FAILURE;
}
