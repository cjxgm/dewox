
#include <GL/gl.h>
#include <math.h>

#include "stacking.h"


#define MAP(V,SF,ST,DF,DT) \
	(((float)(V)-(float)(SF)) \
	/ ((float)(ST)-(float)(SF)) \
	* ((float)(DT)-(float)(DF)) \
	+ (float)(DF))

#ifndef PI
#define PI 3.14159f
#endif


// in this file below.
extern void draw_icon_sine(int x, int y);
extern void draw_icon_env(int x, int y);
extern void draw_icon_mix(int x, int y);
extern void draw_icon_tri(int x, int y);

// in operator.c
extern void opr_sine_render(oprinfo * oi);
extern void opr_env_render(oprinfo * oi);
extern void opr_mix_render(oprinfo * oi);
extern void opr_tri_render(oprinfo * oi);


void draw_cursor(int x, int y)
{
	glLineWidth(1);
  glColor3f(0.8, 0.8, 0.8);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x+2, y+1);
    glVertex2f(x+18, y+10);
    glVertex2f(x+2, y+17);
  glEnd();
}

/* state:
		0	normal
		1	hover
		2	dragging
		3 error (collide)
		4 selected
*/
void draw_operator(int x, int y, int w, int type, int state, oprinfo * oi)
{
	if (state != 2 && state != 3) {
		glColor3f(0.0, 1.0, 0.0);
		glLineWidth(1);
		switch (type) {
			case 0: draw_icon_sine(x, y-1); break;
			case 1: draw_icon_env(x, y-1); break;
			case 2: draw_icon_mix(x, y-1); break;
			case 3: draw_icon_tri(x, y-1); break;
		}
	}
	
	switch (state) {
		case 0:
			glColor3f(0.5, 0.5, 0.5);
			break;
		case 1:
		case 2:
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 3:
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 4:
			glColor3f(1.0, 1.0, 0.0);
			break;
	}
	if (state>1 && state != 4) glLineWidth(2);
	else glLineWidth(1);

  glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x+w, y);
    glVertex2f(x+w, y+20-1);
    glVertex2f(x, y+20-1);
  glEnd();
  
  if (state>1 && state != 4) return;
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0xCCCC);
  glBegin(GL_LINES);
    glVertex2f(x+w-8, y);
    glVertex2f(x+w-8, y+20-1);
  glEnd();
  glDisable(GL_LINE_STIPPLE);
  
  switch (type) {
		case 0: opr_sine_render(oi); break;
		case 1: opr_env_render(oi); break;
		case 2: opr_mix_render(oi); break;
		case 3: opr_tri_render(oi); break;
	}
  glLineWidth(1);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	int i;
	int len = sizeof(oi->rendered)/sizeof(oi->rendered[0]);
	for (i=0; i<len; i++) {
  	glVertex2f(x+MAP(i, 0, len-1, 20, w-9),
				MAP(oi->rendered[i], -32768, 32767, y+18, y+2));
	}
	glEnd();
}

int hovertest_box(int mx, int my, int x, int y, int w, int h)
{
	if (mx<x || mx>x+w || my<y || my>y+h) return 0;
	if (mx>x+w-8) return 2;
	return 1;
}

void draw_icon_sine(int x, int y)
{
	int i;
	glBegin(GL_LINE_STRIP);
	for (i=2; i<=18; i++)
		glVertex2f(x+i, y+MAP(
			sin(MAP(i, 2, 18, 0, 2*PI)),
			-1, 1, 18, 2
		));
	glEnd();
}

void draw_icon_env(int x, int y)
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(x+4, y+10);
		glVertex2f(x+8, y+15);
		glVertex2f(x+16, y+5);
	glEnd();
	
	glPointSize(4);
	glBegin(GL_POINTS);
		glVertex2f(x+4, y+10);
		glVertex2f(x+8, y+15);
		glVertex2f(x+16, y+5);
	glEnd();
	glPointSize(1);
}

void draw_icon_mix(int x, int y)
{
	glBegin(GL_LINES);
		glVertex2f(x+2, y+6);
		glVertex2f(x+10, y+6);
		glVertex2f(x+6, y+2);
		glVertex2f(x+6, y+10);
		
		glVertex2f(x+10, y+14);
		glVertex2f(x+18, y+14);
		glVertex2f(x+14, y+10);
		glVertex2f(x+14, y+18);
	glEnd();
}

void draw_icon_tri(int x, int y)
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(x+2, y+10);
		glVertex2f(x+6, y+2);
		glVertex2f(x+12, y+18);
		glVertex2f(x+18, y+10);
	glEnd();
}
