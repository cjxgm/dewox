
#include <GL/gl.h>
#include "widget.h"
#include "font.h"

int hovertest_box(int mx, int my, int x0, int y0, int x1, int y1)
{
	return (mx>x0 && mx<x1) && (my>y0 && my<y1);
}

// state: 0 normal
//        1 hover
//        2 selected
void draw_button(const char * label, int x0, int y0,
		int x1, int y1, int state)
{
	switch (state) {
	case 0:
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_LINE_LOOP);
		break;
	case 1:
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		break;
	case 2:
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	}
	glVertex2f(x0, y0);
	glVertex2f(x1, y0);
	if (state == 2) glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(x1, y1);
	glVertex2f(x0, y1);
	glEnd();

	// draw label
	if (y1-y0 < 16) return;
	if (state == 2) glColor3f(1.0f, 1.0f, 1.0f);
	draw_string_centered((x0+x1-8)/2, (y0+y1-16)/2, x1-x0, label, 0);
}

