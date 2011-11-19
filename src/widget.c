
#include <GL/gl.h>
#include "widget.h"
#include "font.h"




// pager widgets

void draw_page_button(const char * label, int x, int y,
		int w, int h, WStyle style)
{
	switch (style) {
	case WSTYLE_NORMAL:
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_LINE_LOOP);
		break;
	case WSTYLE_HOVERED:
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		break;
	case WSTYLE_SELECTED:
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	if (style == WSTYLE_SELECTED) glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glEnd();

	// draw label
	if (h < 16) return;
	if (style == WSTYLE_SELECTED) glColor3f(1.0f, 1.0f, 1.0f);
	draw_string_centered(x+(w-8)/2, y+(h-16)/2, w, label, 0);
}




// -- split

void draw_split(WSplit * widget)
{
	if (widget->type == WSPLIT_HOR) {
		glColor3f(0.2, 0.2, 0.2);
		glRectf(widget->low, widget->value-10,
				widget->high, widget->value+10);

		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINES);
		glVertex2f(widget->high, widget->value-10);
		glVertex2f(widget->low,  widget->value-10);
		glVertex2f(widget->high, widget->value+10);
		glVertex2f(widget->low,  widget->value+10);
		glEnd();
	}
	
	else {
		glColor3f(0.2, 0.2, 0.2);
		glRectf(widget->value-10, widget->low,
				widget->value+10, widget->high);

		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINES);
		glVertex2f(widget->value-10, widget->high);
		glVertex2f(widget->value-10, widget->low );
		glVertex2f(widget->value+10, widget->high);
		glVertex2f(widget->value+10, widget->low );
		glEnd();
	}
}

void hover_split(WSplit * widget, int x, int y)
{
	if (widget->style == WSTYLE_NORMAL) {
	}
}

void drag_split(WSplit * widget, int x, int y)
{
	if (widget->style == WSTYLE_DRAGGING) {
		int t = (widget->type == WSPLIT_HOR ? y : x);
		widget->value += t - widget->tmp;
		widget->tmp    = t;
	}
}

void click_split(WSplit * widget, int button, int state, int x, int y)
{
}




// hover tests
int hovertest_box(int mx, int my, int x, int y, int w, int h)
{
	return (mx>x && mx<x+w) && (my>y && my<y+h);
}

