
/************************************************************
 * dewox: ui.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "ui.h"
#include <stdio.h>
#include <GL/gl.h>

void draw_edge_y(int x, int h)
{
	glLineWidth(4);
	glColor3f(0.2f, 0.2f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(x, 0);
	glVertex2f(x, h);
	glEnd();
}

void draw_edge_x(int y, int w)
{
	glLineWidth(4);
	glColor3f(0.2f, 0.2f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, y);
	glVertex2f(w, y);
	glEnd();
}

void draw_box_up(int x, int y, int w, int h,
		float r, float g, float b)
{
	if (w <= 0 || h <= 0) return;

	glBegin(GL_QUADS);
	glColor3f(r * 0.8f, g * 0.8f, b * 0.8f);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glColor3f(r / 0.8f, g / 0.8f, b / 0.8f);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glEnd();
}

void draw_box_down(int x, int y, int w, int h,
		float r, float g, float b)
{
	if (w <= 0 || h <= 0) return;

	glBegin(GL_QUADS);
	glColor3f(r * 1.2f, g * 1.2f, b * 1.2f);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glColor3f(r / 1.2f, g / 1.2f, b / 1.2f);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glEnd();
}

void draw_outline(int x, int y, int w, int h)
{
	if (w <= 0 || h <= 0) return;

	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor4f(0.2f, 0.2f, 1.0f, 0.2f);
	glVertex2f(x-1, y-1);
	glVertex2f(x+w+1, y-1);
	glVertex2f(x+w+1, y+h+1);
	glVertex2f(x-1, y+h+1);
	glColor4f(0.2f, 0.2f, 1.0f, 0.6f);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glColor4f(0.2f, 0.2f, 1.0f, 1.0f);
	glVertex2f(x+1, y+1);
	glVertex2f(x+w-1, y+1);
	glVertex2f(x+w-1, y+h-1);
	glVertex2f(x+1, y+h-1);
	glEnd();
}

void draw_button(int x, int y, int w, int h, int state)
{
	if (w <= 0 || h <= 0) return;

	switch (state) {
		case UI_BUTTON_STATE_NORMAL:
			draw_box_up(x, y, w, h, 0.2, 0.2, 0.2);
			break;
		case UI_BUTTON_STATE_ACTIVE:
			draw_box_up(x, y, w, h, 0.25, 0.25, 0.25);
			break;
		case UI_BUTTON_STATE_PRESSED:
			draw_box_down(x, y, w, h, 0.2, 0.5, 1.0);
			break;
		case UI_BUTTON_STATE_TOGGLED:
			draw_box_down(x, y, w, h, 1.0, 0.5, 0.2);
			break;
	}
	// draw border
	glLineWidth(0.1f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glEnd();
}




// parameter widgets
static char buf[32];

void draw_float_box(DParam * p, int x, int y, int w, int h, int state)
{
	glPointSize(1);
	switch (state) {
		case UI_BUTTON_STATE_NORMAL:
			if (p->meta->p2 == p->meta->p3)
				draw_button(x, y, w, h, UI_BUTTON_STATE_NORMAL);
			else {
				draw_button(x, y, w, h, UI_BUTTON_STATE_PRESSED);
				draw_button(x+1, y+1,
						lerp(p->f, p->meta->p2, p->meta->p3, 0, w)-2,
						h-2, UI_BUTTON_STATE_NORMAL);
			}
			break;
	}
	glColor3f(1.0, 1.0, 1.0);
	sprintf(buf, "%g", p->f);
	font_renderw(buf, x+10, y, w-20);
}

void draw_vec_box(DParam * p, int x, int y, int w, int h,
		int state, int btn)
{
	float ew = w / 3.0f;

	glPointSize(1);
	switch (state) {
		case UI_BUTTON_STATE_NORMAL:
			draw_button(x, y, ew, h, UI_BUTTON_STATE_NORMAL);
			draw_button(x+ew, y, ew, h, UI_BUTTON_STATE_NORMAL);
			draw_button(x+ew+ew, y, ew, h, UI_BUTTON_STATE_NORMAL);
			break;
	}
	glColor3f(1.0, 1.0, 1.0);
	sprintf(buf, "%g", p->v[0]);
	font_renderw(buf, x+10, y, ew-20);
	sprintf(buf, "%g", p->v[1]);
	font_renderw(buf, x+ew+10, y, ew-20);
	sprintf(buf, "%g", p->v[2]);
	font_renderw(buf, x+ew+ew+10, y, ew-20);
}

void draw_color_box(DParam * p, int x, int y, int w, int h,
		int state, int btn)
{
	if (w < 18) return;

	w -= 20;
	float ew = w / 3.0f;

	glPointSize(1);
	switch (state) {
		case UI_BUTTON_STATE_NORMAL:
			draw_button(x, y, ew, h, UI_BUTTON_STATE_PRESSED);
			draw_button(x+ew, y, ew, h, UI_BUTTON_STATE_PRESSED);
			draw_button(x+ew+ew, y, ew, h, UI_BUTTON_STATE_PRESSED);
			draw_button(x+1, y+1, ew*p->v[0]-2, h-2,
					UI_BUTTON_STATE_NORMAL);
			draw_button(x+ew+1, y+1, ew*p->v[1]-2, h-2,
					UI_BUTTON_STATE_NORMAL);
			draw_button(x+ew+ew+1, y+1, ew*p->v[2]-2, h-2,
					UI_BUTTON_STATE_NORMAL);
			break;
	}
	glColor3f(1.0, 1.0, 1.0);
	sprintf(buf, "%g", p->v[0]);
	font_renderw(buf, x+10, y, ew-20);
	sprintf(buf, "%g", p->v[1]);
	font_renderw(buf, x+ew+10, y, ew-20);
	sprintf(buf, "%g", p->v[2]);
	font_renderw(buf, x+ew+ew+10, y, ew-20);

	glColor3f(p->v[0], p->v[1], p->v[2]);
	glRectf(x+w+2, y, x+w+20, y+h);
}

