
#include <GL/gl.h>
#include "widget.h"
#include "config.h"
#include "font.h"

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

void draw_msgbox(float x, float y, float w,
		const char * title, const char * label, WState state)
{
	glBegin(GL_QUADS);
		glColor3f(COLOR_MSGBOX_TITLE1);
		glVertex2f(x+w, y);
		glVertex2f(x, y);

		glColor3f(COLOR_MSGBOX_TITLE2);
		glVertex2f(x, y+40);
		glVertex2f(x+w, y+40);
	glEnd();
	glColor3f(COLOR_MSGBOX_TITLE3);
	draw_string(x+4, y+4, w-4, title, 0.0f);

	y += 20;
	x += 2;
	w -= 4;
	if (state == WSTATE_HOVERED) {
		glBegin(GL_QUADS);
			glColor3f(COLOR_MSGBOX_HOVERED1);
			glVertex2f(x+w, y);
			glVertex2f(x, y);

			glColor3f(COLOR_MSGBOX_HOVERED2);
			glVertex2f(x, y+18);
			glVertex2f(x+w, y+18);
		glEnd();
		glColor3f(COLOR_MSGBOX_HOVERED3);
	}
	else glColor3f(COLOR_MSGBOX_NORMAL);
	draw_string(x+20, y+4, w-20, label, 0.0f);
}

