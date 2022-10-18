#ifndef __CHARACTER_H_
#define __CHARACTER_H_
struct pos {
	int x;
	int y;
};

void s_init(int width, int height);
void s_setLimits(int width, int height);
void s_changePos();
void s_setDir(int x, int y);
void s_eat(int x, int y);
void s_update();


#endif
