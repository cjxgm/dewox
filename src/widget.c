
#include <GL/gl.h>
#include "widget.h"

int hovertest_box(int mx, int my, int x0, int y0, int x1, int y1)
{
	return (mx>x0 && mx<x1) && (my>y0 && my<y1);
}

void draw_button(const char * name, int x0, int y0, int x1, int y1)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(x0, y0);
	glVertex2f(x1, y0);
	glVertex2f(x1, y1);
	glVertex2f(x0, y1);
	glEnd();
}

