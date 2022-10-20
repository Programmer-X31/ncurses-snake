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
#include <unistd.h>
#include "players.h"

static struct pos s_head = {10, 5};
static struct pos s_last;

static struct pos *s_tail;
static int s_size = 1;

static int s_xoff, s_yoff;
static char ch, s_mode = 'r';


bool includes(struct pos val, struct pos arr[], int len) {
    int i;
    for(i = 0; i < len-2; i++){
		if(arr[i].x == val.x && arr[i].y == val.y)
			return true;
    }
    return false;
}

void s_init(int width, int height)
{
	s_tail = calloc(s_size, sizeof(struct pos));
	t_width = width;
	t_height = height;
	
	s_setDir(1, 0);
	s_mode = 'r';
	s_update();

	mvprintw(1, 3, "Score: %d", score);
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

void s_update()
{
	if(gameRunning) {
		mvaddch(s_last.y, s_last.x, ' ');
		for(int i = 0; i < s_size; i++) {
			attron(COLOR_PAIR(2));
			mvprintw(s_tail[i].y, s_tail[i].x, "█");
		}

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
		s_last = s_tail[0];
		for(int i = 0; i < s_size - 1; i++)
			s_tail[i] = s_tail[i + 1];

		s_tail[s_size - 1] = s_head;

		int x = s_head.x + s_xoff;
		int y = s_head.y + s_yoff;

		if(x > t_width) /* Right End */
			s_head.x = 0;
		else if (x < 0) /* Left Side */
			s_head.x = t_width;
		else if (y > t_height) /* Down Side */
			s_head.y = 0;
		else if (y < 0) /* Up side */
			s_head.y = t_height;
		else {
			if(!includes(s_head, s_tail, s_size)) {
				 s_head.x = x;
				 s_head.y = y;
			} 
			else {
				gameRunning = false;
			}
		}
		struct pos food_loc = f_getLoc();
		if(s_head.x == food_loc.x && s_head.y == food_loc.y) {
			s_grow();
			++score;
			mvprintw(1, 3, "Score: %d", score);
			f_pickLoc();
		}
	} else {
		clear();
		mvprintw(t_height/2, t_width/2-4, " Game Over ");
		mvprintw(t_height/2 + 1, t_width/2-9, "Press Any Key to Exit");
		timeout(-1);
		getch();
		endwin();
		exit(0);
	}
}




