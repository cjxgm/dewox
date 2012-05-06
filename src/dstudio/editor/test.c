
/************************************************************
 * dewox: test.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "../wm.h"
#include <GL/gl.h>

static void render(int w, int h);

void editor_test_init()
{
	wm_register_editor("Test", render);
}

static void render(int w, int h)
{
	glBegin(GL_POINTS);
	int x,y;
	for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			glColor3f(x/(float)w, y/(float)h,
						x*y/(float)w/(float)h);
			glVertex2f(x, y);
		}
	glEnd();
}

