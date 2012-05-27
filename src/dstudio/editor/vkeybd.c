
/************************************************************
 * dewox: vkeybd
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"
#include "../../dshared/dshared.h"
#include <stdio.h>

static void draw_whitekey(int x, int w, int h);
static void draw_blackkey(int x, int w, int h);

static char blacks[7] = {1, 1, 1, 0, 1, 1, 0};
static int sx = 0;
static int dragbtn = 0;
static int dragx = 0;

void editor_vkeybd_init()
{
	REGISTER_EDITOR("Virtual Keyboard");
}

static void render(int w, int h)
{
	int i;
	int x;

	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(sx, 0, sx+49*20, h);
	glLineWidth(1.0f);
	glPointSize(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

	for (i=0; i<49; i++) {
		x = sx + i*20;
		if (x<-20) continue;
		if (x>w) break;
		draw_whitekey(x, 20, h);
		if (i%7 == 0) {
			char buf[2];
			sprintf(buf, "%d", i/7 + 1);
			font_render(buf, x+6, 4);
		}
	}

	glColor3f(0.0f, 0.0f, 0.0f);
	for (i=0; i<49; i++)
		if (blacks[i%7]) {
			x = sx + i*20 + 14;
			if (x<-12) continue;
			if (x>w) break;
			draw_blackkey(x, 12, h);
		}
}

static void hover(int x, int y, int w, int h)
{
}

static void click(int x, int y, int w, int h, int btn, int stt)
{
	if (stt == WM_BUTTON_DOWN && btn == WM_BUTTON_MID) {
		dragbtn = WM_BUTTON_MID;
		dragx = x;
	}
	if (stt == WM_BUTTON_UP && btn == WM_BUTTON_MID) {
		dragbtn = 0;
	}
}

static void drag(int x, int y, int w, int h)
{
	if (dragbtn == WM_BUTTON_MID) {
		sx += x - dragx;
		dragx = x;
		if (sx < -49*20+w) sx = -49*20+w;
		if (sx > 0) sx = 0;
		wm_require_refresh();
	}
}

static void draw_whitekey(int x, int w, int h)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, 0);
	glVertex2f(x+w, 0);
	glVertex2f(x+w, h);
	glVertex2f(x, h);
	glEnd();
}

static void draw_blackkey(int x, int w, int h)
{
	glRectf(x, h*0.382, x+w, h);
}

static void keypress(int key, int w, int h)
{
}

