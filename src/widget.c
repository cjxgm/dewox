
#include <GL/gl.h>
#include "widget.h"
#include "font.h"

int hovertest_box(int mx, int my, int x, int y, int w, int h)
{
	return (mx>x && mx<x+w) && (my>y && my<y+h);
}

// state: 0 normal
//        1 hover
//        2 selected
void draw_button(const char * label, int x, int y,
		int w, int h, int state)
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
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	if (state == 2) glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glEnd();

	// draw label
	if (y+h-y < 16) return;
	if (state == 2) glColor3f(1.0f, 1.0f, 1.0f);
	draw_string_centered((x+x+w-8)/2, (y+y+h-16)/2, w, label, 0);
}

