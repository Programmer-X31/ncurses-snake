/*
 * =====================================================================================
 *
 *       Filename:  snake2.c
 *
 *    Description: Reimplentation of Snake Clsass 
 *
 *        Version:  1.0
 *        Created:  10/15/2022 16:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sachin Murali (), sachinsamurai@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <ncurses.h>
#include <stdlib.h>
#include "players.h"

struct pos s_head = {10, 5};
struct pos s_last;

struct pos *s_tail;
int s_size = 10;

int s_xoff, s_yoff;
int tw = 100, th = 20;
char ch;

void s_init(int width, int height)
{
	s_tail = calloc(s_size, sizeof(struct pos));
	tw = width;
	th = height;
}

void s_setDir(int xoff, int yoff)
{
	s_xoff = xoff;
	s_yoff = yoff;
}

void s_changePos()
{
	s_last = s_tail[0];
	for(int i = 0; i < s_size - 1; i++)
		s_tail[i] = s_tail[i + 1];
	s_tail[s_size - 1] = s_head;


	if((s_head.x + s_xoff) > tw) /* Right End */
		s_head.x = 0;
	else if ((s_head.x + s_xoff) < 0) /* Left Side */
		s_head.x = tw;
	else if ((s_head.y + s_yoff) > th) /* Down Side */
		s_head.y = 0;
	else if ((s_head.y + s_yoff) < 0) /* Up side */
		s_head.y = th;
	else {
		s_head.x += s_xoff;
		s_head.y += s_yoff;
	}

}

void s_update()
{
	mvaddch(s_last.y, s_last.x, ' ');
	for(int i = 0; i < s_size; i++)
		mvaddch(s_tail[i].y, s_tail[i].x, 'S');

	ch = getch();

	switch(ch) {
		case 'w':
			s_setDir(0, -1);
			break;
		case 'a':
			s_setDir(-1, 0);
			break;
		case 's':
			s_setDir(0, 1);
			break;
		case 'd':
			s_setDir(1, 0);
			break;
		case 'x':
			endwin();
			exit(0);
			break;
	}


	s_changePos();
}



