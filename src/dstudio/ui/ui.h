
/************************************************************
 * dewox: ui.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __UI_H
#define __UI_H

#include "menu.h"




void draw_edge_y(int x, int h);
void draw_edge_x(int y, int w);
void draw_box_up(int x, int y, int w, int h,
		float r, float g, float b);
void draw_box_down(int x, int y, int w, int h,
		float r, float g, float b);
void draw_outline(int x, int y, int w, int h);

#define UI_BUTTON_STATE_NORMAL		0
#define UI_BUTTON_STATE_ACTIVE		1
#define UI_BUTTON_STATE_PRESSED		2
void draw_button(int x, int y, int w, int h, int state);

#endif

