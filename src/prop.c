
#include <GL/glut.h>

#include "stacking.h"

#define MAP(V,SF,ST,DF,DT) \
	(((float)(V)-(float)(SF)) \
	/ ((float)(ST)-(float)(SF)) \
	* ((float)(DT)-(float)(DF)) \
	+ (float)(DF))

static int dragging = 0;
static int dragging_x, dragging_y;

void prop_draw(oprinfo * oi)
{
	glLineWidth(1);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINE_LOOP);
		glVertex2f(10, 10);
		glVertex2f(190, 10);
		glVertex2f(190, 30);
		glVertex2f(10, 30);
	glEnd();
	
	glColor3f(0.0, 0.5, 0.5);
	float w = MAP(oi->step, 1.0f/54.0f, 1.0f/5.0f, 0, 178);
	glRectf(11, 11, 11+w, 29);
}

void prop_click(int btn, int stt, int x, int y)
{
	if (btn == GLUT_LEFT && stt == GLUT_DOWN) {
		dragging = (x>10 && x<190 && y>10 && y<190);
		if (dragging) {
			dragging_x = x;
			dragging_y = y;
		}
	}
	
	if (btn == GLUT_LEFT && stt == GLUT_UP) {
		dragging = 0;
	}
}

void prop_drag(int x, int y, oprinfo * oi)
{
	if (!dragging) return;
	oi->step += MAP(x-dragging_x, 0, 178, 0, 1.0f/5.0f-1.0f/54.0f);
	if (oi->step > 1.0f/5.0f) oi->step = 1.0f/5.0f;
	if (oi->step < 1.0f/54.0f) oi->step = 1.0f/54.0f;
	dragging_x = x;
}
