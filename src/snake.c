/*
 * =====================================================================================
 *
 *       Filename:  snake.c
 *
 *    Description:  Implentation of Snake Clsass 
 *
 *        Version:  1.0
 *        Created:  10/15/2022 16:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sachin Murali (), sachinsamurai@gmail.com
 *
 * =====================================================================================
 */

#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "players.h"

static struct pos s_head = {10, 5};
static struct pos s_last;

static struct pos *s_tail;
static int s_size = 50;

static int s_xoff, s_yoff;
static int tw = 100, th = 20;
static char ch, s_mode = 'r';


bool includes(struct pos val, struct pos arr[], int len) {
    int i;
    for(i = 0; i < len; i++){
		if(arr[i].x == val.x && arr[i].y == val.y)
				return true;
    }
    return false;
}

void s_init(int width, int height)
{
	s_tail = calloc(s_size, sizeof(struct pos));
	tw = width;
	th = height;
	setlocale(LC_ALL, "");
}

void s_setDir(int xoff, int yoff)
{
	s_xoff = xoff;
	s_yoff = yoff;
}

void s_grow()
{
	s_size++;
	s_tail = realloc(s_tail, sizeof(struct pos) * s_size);
}

void s_changePos()
{
	s_last = s_tail[0];
	for(int i = 0; i < s_size - 1; i++)
		s_tail[i] = s_tail[i + 1];
	s_tail[s_size - 1] = s_head;

	int x = s_head.x + s_xoff;
	int y = s_head.y + s_yoff;

	if(x > tw) /* Right End */
		s_head.x = 0;
	else if (x < 0) /* Left Side */
		s_head.x = tw;
	else if (y > th) /* Down Side */
		s_head.y = 0;
	else if (y < 0) /* Up side */
		s_head.y = th;
	else {
		// TODO: Use Distance Formula to find distance between the points within the snake
		// TODO: Add Collision detection

		/* if(s_size > 2) { 
		     if(!includes(s_head, s_tail, s_size)) {
		         s_head.x = x; 
		         s_head.x = x; 
		     } 
		 } 
		 else { 
			s_head.x += s_xoff;
			s_head.y += s_yoff;
		} */
		
		s_head.x += s_xoff;
		s_head.y += s_yoff;
	}
}

void s_update()
{
	mvaddch(s_last.y, s_last.x, ' ');
	for(int i = 0; i < s_size; i++)
		mvprintw(s_tail[i].y, s_tail[i].x, "█");

	ch = getch();

	switch(ch) {
		case 'w':
			if(s_mode != 'b') 
			{
				s_setDir(0, -1);
				s_mode = 'f';
			}
			break;
		case 'a':
			if(s_mode != 'r') 
			{
				s_setDir(-1, 0);
				s_mode = 'l';
			}
			break;
		case 's':
			if(s_mode != 'f') 
			{
				s_setDir(0, 1);
				s_mode = 'b';
			}
			break;
		case 'd':
			if(s_mode != 'l')
			{
				s_setDir(1, 0);
				s_mode = 'r';
			}
			break;
		case 'x':
			endwin();
			exit(0);
			break;
	}
	s_changePos();
}




