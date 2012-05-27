
/************************************************************
 * dewox: welcome
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"
#include "../../dshared/dshared.h"

void editor_welcome_init()
{
	REGISTER_EDITOR("Welcome");
}

static void render(int w, int h)
{
	glPointSize(1);
	glColor3f(0.0f, 1.0f, 0.0f);
	font_render("Welcome to Dewox!", 10, h-30);

	glColor3f(1.0f, 1.0f, 1.0f);
	font_render("Dewox has a flexible UI.", 20, 90);

	glLineWidth(2);
	glColor3f(1.0f, 0.5f, 0.2f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(80, 0);
	glVertex2f(90, 20);
	glVertex2f(120, 20);
	glEnd();
	font_render("Editor Selector", 124, 10);

	glBegin(GL_LINE_STRIP);
	glVertex2f(50, 0);
	glVertex2f(70, 40);
	glVertex2f(104, 40);
	glEnd();
	font_render("Verticle Splitter", 108, 30);

	glBegin(GL_LINE_STRIP);
	glVertex2f(30, 0);
	glVertex2f(58, 60);
	glVertex2f(88, 60);
	glEnd();
	font_render("Horizontal Splitter", 92, 50);

	glBegin(GL_LINE_STRIP);
	glVertex2f(10, 0);
	glVertex2f(46, 80);
	glVertex2f(136, 80);
	glEnd();
	font_render("Window Killer", 140, 70);

	// draw the logo!
	float logosize[2];
	d_logo_get_size(&logosize[0], &logosize[1]);
	d_logo_draw((w-logosize[0]) / 2.0f, (h-logosize[1]) / 2.0f);
}

static void hover(int x, int y, int w, int h)
{
}

static void click(int x, int y, int w, int h, int btn, int stt)
{
}

static void drag(int x, int y, int w, int h)
{
}

static void keypress(int key, int w, int h)
{
}

