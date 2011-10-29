
#include <GL/gl.h>
#include "widget.h"
#include "font.h"

int hovertest_box(int mx, int my, int x0, int y0, int x1, int y1)
{
	return (mx>x0 && mx<x1) && (my>y0 && my<y1);
}

void draw_button(const char * label, int x0, int y0, int x1, int y1)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(x0, y0);
	glVertex2f(x1, y0);
	glVertex2f(x1, y1);
	glVertex2f(x0, y1);
	glEnd();

	// draw label
	if (y1-y0 < 16) return;
	draw_string_centered((x0+x1-8)/2, (y0+y1-16)/2, x1-x0, label, 0);
}

