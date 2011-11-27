
#include <GL/gl.h>
#include "widget.h"
#include "../config.h"

int hovertest_box(int mx, int my, int x, int y, int w, int h)
{
	return ((mx > x && mx < x+w) && (my > y && my < y+h));
}

void draw_border(int x, int y, int w, int h)
{
	glLineWidth(0.1f);
	glColor3f(COLOR_BORDER);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x+w, y);
		glVertex2f(x, y);
		glVertex2f(x, y+h);
		glVertex2f(x+w, y+h);
	glEnd();
}

