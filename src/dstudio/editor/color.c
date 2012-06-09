
/************************************************************
 * dewox: color
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"
#include "../ui/ui.h"
#include <stdio.h>

static UIMenu menu[] = {
	{UI_MENU_DONE}
};

static float r = 1.0f;
static float g = 0.5f;
static float b = 0.2f;

static int active_slider = 0;

void editor_color_init()
{
	REGISTER_EDITOR("Color Picker");
}

static void render(int w, int h)
{
	glColor3f(r, g, b);
	glRectf(0, 0, w, h);

	// draw outsize
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(4);
	glBegin(GL_LINES);
	// b
	glVertex2f(20-2, 20);
	glVertex2f(120+2, 20);
	// g
	glVertex2f(20-2, 40);
	glVertex2f(120+2, 40);
	// r
	glVertex2f(20-2, 60);
	glVertex2f(120+2, 60);
	glEnd();

	// draw internal
	glColor3f(0.5f, 0.5f, 0.5f);
	glLineWidth(2);
	glBegin(GL_LINES);
	// b
	glVertex2f(20, 20);
	glVertex2f(120, 20);
	// g
	glVertex2f(20, 40);
	glVertex2f(120, 40);
	// r
	glVertex2f(20, 60);
	glVertex2f(120, 60);
	glEnd();

	// draw slider
	float x;
	char buf[16];
	switch (active_slider) {
		case 1:
			x = 20 + 100 * r;
			draw_box_up(x-6, 60-6, 12, 12, 0.5, 0.5, 0.5);
			draw_box_up(x-5, 60-5, 10, 10, r, 0, 0);
			glPointSize(1);
			glColor3f(1.0f-r, 1.0f-g, 1.0f-b);
			sprintf(buf, "%g", r);
			font_render(buf, 128, 50);
			break;
		case 2:
			x = 20 + 100 * g;
			draw_box_up(x-6, 40-6, 12, 12, 0.5, 0.5, 0.5);
			draw_box_up(x-5, 40-5, 10, 10, 0, g, 0);
			glPointSize(1);
			glColor3f(1.0f-r, 1.0f-g, 1.0f-b);
			sprintf(buf, "%g", g);
			font_render(buf, 128, 30);
			break;
		case 3:
			x = 20 + 100 * b;
			draw_box_up(x-6, 20-6, 12, 12, 0.5, 0.5, 0.5);
			draw_box_up(x-5, 20-5, 10, 10, 0, 0, b);
			glPointSize(1);
			glColor3f(1.0f-r, 1.0f-g, 1.0f-b);
			sprintf(buf, "%g", b);
			font_render(buf, 128, 10);
			break;
	}
}

static void hover(int x, int y, int w, int h)
{
	if (x > 125 || x < 15 || y > 65 || y < 15) {
		if (active_slider) {
			active_slider = 0;
			wm_require_refresh();
		}
		return;
	}

	int t = 0;
	if (y >= 55 && y <= 65) t = 1;
	else if (y >= 35 && y <= 45) t = 2;
	else if (y >= 15 && y <= 25) t = 3;
	if (active_slider != t) {
		active_slider = t;
		wm_require_refresh();
	}
}

static void click(int x, int y, int w, int h, int btn, int stt)
{
	if (btn == WM_BUTTON_LEFT && stt == WM_BUTTON_DOWN)
		drag(x, y, w, h);
}

static void drag(int x, int y, int w, int h)
{
	if (!active_slider) return;

	float t = (x - 20) / 100.0f;
	if (t < 0) t = 0.0f;
	else if (t > 1) t = 1.0f;

	switch (active_slider) {
		case 1: r = t; break;
		case 2: g = t; break;
		case 3: b = t; break;
	}

	wm_require_refresh();
}

static void keypress(int key, int w, int h)
{
}

