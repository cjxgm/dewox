
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

	// draw white keys
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(sx, 0, sx+49*20, h);
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (i=0; i<49-1; i++) {
		x = sx + i*20;
		if (x<-20) continue;
		if (x>w) break;
		glVertex2f(x+20, 0);
		glVertex2f(x+20, h);
	}
	glEnd();

	// draw octaves
	glPointSize(1.0f);
	for (i=0; i<7; i++) {
		char buf[2];
		x = sx + i*20*7;
		sprintf(buf, "%d", i + 1);
		font_render(buf, x+6, 4);
	}

	// draw black keys
	for (i=0; i<49; i++)
		if (blacks[i%7]) {
			x = sx + i*20 + 14;
			if (x<-12) continue;
			if (x>w) break;
			glRectf(x, h*0.382, x+12, h);
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

static void keypress(int key, int w, int h)
{
}

