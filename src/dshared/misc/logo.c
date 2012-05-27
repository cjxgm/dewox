
/************************************************************
 * dewox: logo.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "logo.h"
#include "../font/font.h"
#include "../math/erp.h"
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

#ifndef PI
# define PI 3.1415927f
#endif

// draw circle at (x, y) radius as r from angle a1 to angle a2.
static void draw_circle(int primitive,
		float x, float y, float r, float a1, float a2);
static void draw_dew(float x, float y);
static void draw_x(float x, float y);
static void draw_highlight(float x, float y, float r, float a);

void d_logo_draw(float x, float y)
{
	glLineWidth(3.0f);
	glColor3f(1.0f, 0.5f, 0.2f);
	draw_circle(GL_LINE_STRIP, x+30, y+30, 30, 0, 2.0f*PI);

	draw_x(x+70, y+10);

	glLineWidth(2.0f);
	glColor3f(0.2f, 0.5f, 1.0f);
	draw_dew(x+7, y+18);
}

int d_logo_draw_init(float x, float y, int stage, int param)
{
	static char buf[4];
	static char title[] = "A Procedural Generation Studio";
	if (stage == 0) {
		glLineWidth(3.0f);
		glColor3f(1.0f, 0.5f, 0.2f);
		draw_circle(GL_LINE_STRIP, x+55, y+30, 50, 0, 2.0f*PI*param/100);
		sprintf(buf, "%d", param);
		glColor3f(0.5f, 1.0f, 0.2f);
		glPointSize(1.0f);
		font_render(buf, x + 55-(font_width(buf)>>1), y+22);
	}
	else if (stage == 1) {
		if (param < 200) {
			float a = ferp_out(param, 0, 200, 1, 0);
			glLineWidth(3.0f);
			glColor3f(1.0f, 0.5f, 0.2f);
			draw_circle(GL_LINE_STRIP, x+55, y+30, 20 + a*30, 0, 2.0f*PI);
			sprintf(buf, "%d", 100);
			glColor3f(0.5f*a, 1.0f*a, 0.2f*a);
			glPointSize(1.0f);
			font_render(buf, x + 55-(font_width(buf)>>1), y+22);
		}
		else if (param < 300) {
			float a = ferp_in(param, 200, 300, 0, 10);
			glLineWidth(3.0f);
			glColor3f(1.0f, 0.5f, 0.2f);
			draw_circle(GL_LINE_STRIP, x+55, y+30, 20 + a, 0, 2.0f*PI);
		}
		else if (param < 500) {
			float a = ferp_out(param, 300, 500, 0, 1);
			float b = ferp_in (param, 300, 500, 0, 1);

			glLineWidth(3.0f);
			glColor3f(1.0f, 0.5f, 0.2f);
			draw_circle(GL_LINE_STRIP, x+55 - a*25, y+30,
						30, 0, 2.0f*PI);
			draw_highlight(x+55 - a*25, y+30,
						30, lerp(param, 300, 500, 0, 2*PI));

			glColor4f(1.0f, 0.5f, 0.2f, b);
			draw_x(x+70, y+10);

			glLineWidth(2.0f);
			glColor4f(0.2f, 0.5f, 1.0f, b);
			draw_dew(x+7, y+18);
		}
		else if (param < 1000) {
			float a = ferp_out(param, 500, 1000, 0, 1);
			float b = ferp_in (param, 500, 1000, 0, 1);
			d_logo_draw(x, y + a*12);

			glPointSize(1.0f);
			glColor4f(0.5f, 1.0f, 0.2f, b);
			font_render(title, x + 55-(font_width(title)>>1),
							   y - b*12);
		}
		else if (param < 2500) {
			d_logo_draw(x, y + 12);
			glPointSize(1.0f);
			glColor3f(0.5f, 1.0f, 0.2f);
			font_render(title, x + 55-(font_width(title)>>1),
							   y - 12);
		}
		else return 1;
	}
	return 0;
}

void d_logo_get_size(float * w, float * h)
{
	*w = 110.0f;
	*h = 60.0f;
}

static void draw_circle(int primitive,
		float x, float y, float r, float a1, float a2)
{
	float step = 1.0f / r;
	glBegin(primitive);
	for (; a1<a2; a1+=step)
		glVertex2f(x + r*cos(a1), y + r*sin(a1));
	glEnd();
}

static void draw_dew(float x, float y)
{
	// D
	draw_circle(GL_LINE_STRIP, x, y+12, 12, -PI/2, PI/2);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x, y+24);
	glEnd();
	// E
	glBegin(GL_LINE_STRIP);
	glVertex2f(x+30, y);
	glVertex2f(x+18, y);
	glVertex2f(x+18, y+24);
	glVertex2f(x+30, y+24);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x+18, y+12);
	glVertex2f(x+30, y+12);
	glEnd();
	// W
	glBegin(GL_LINE_STRIP);
	glVertex2f(x+34, y+24);
	glVertex2f(x+37, y);
	glVertex2f(x+40, y+16);
	glVertex2f(x+43, y);
	glVertex2f(x+46, y+24);
	glEnd();
}

static void draw_x(float x, float y)
{
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x+40, y+40);
	glVertex2f(x, y+40);
	glVertex2f(x+40, y);
	glEnd();
}

static void draw_highlight(float x, float y, float r, float a)
{
	float b;
	float step = 1.0f / 10.0f;
	float ox = x + r*cos(a);
	float oy = y + r*sin(a);

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex2f(ox, oy);
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	for (b=0; b<2*PI; b+=step)
		glVertex2f(ox + 10*cos(b), oy + 10*sin(b));
	b += step;	// otherwise, there will be a "gap"
	glVertex2f(ox + 10*cos(b), oy + 10*sin(b));
	glEnd();
}

