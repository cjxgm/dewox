
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
#include "../../dshared/dshared.h"




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
#define UI_BUTTON_STATE_TOGGLED		3
void draw_button(int x, int y, int w, int h, int state);




// parameter widgets
void draw_float_box(DParam * p, int x, int y, int w, int h, int state);
void draw_vec_box(DParam * p, int x, int y, int w, int h,
		int state, int btn);
void draw_color_box(DParam * p, int x, int y, int w, int h,
		int state, int btn);


int  is_in_box(float x, float y, float x1, float y1, float x2, float y2);

#endif

