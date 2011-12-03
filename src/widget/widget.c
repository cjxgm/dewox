
#include <GL/gl.h>
#include "widget.h"
#include "../config.h"
#include "../font.h"

float hovertest_box(float mx, float my,
		float x, float y, float w, float h)
{
	return ((mx > x && mx < x+w) && (my > y && my < y+h));
}

void draw_border(float x, float y, float w, float h)
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

