
#include <GL/gl.h>
#include <string.h>

#include "range.h"
#include "window.h"
#include "config.h"
#include "dutil.h"
#include "event.h"
#include "font.h"

char buf_editing[20] = {0};


void wrange_draw(WRange * w)
{
	glBegin(GL_QUADS);
		switch (w->state) {
			case WSTATE_NORMAL:  glColor3f(COLOR_WRANGE_NORMAL1);  break;
			case WSTATE_HOVERED: glColor3f(COLOR_WRANGE_HOVERED1); break;
			case WSTATE_EDITING:
			case WSTATE_PRESSED: glColor3f(COLOR_WRANGE_PRESSED1); break;
			default: break;
		}
		glVertex2f(w->x + w->w, w->y);
		glVertex2f(w->x, w->y);

		switch (w->state) {
			case WSTATE_NORMAL:  glColor3f(COLOR_WRANGE_NORMAL2);  break;
			case WSTATE_HOVERED: glColor3f(COLOR_WRANGE_HOVERED2); break;
			case WSTATE_EDITING:
			case WSTATE_PRESSED: glColor3f(COLOR_WRANGE_PRESSED2); break;
			default: break;
		}
		glVertex2f(w->x, w->y + w->h);
		glVertex2f(w->x + w->w, w->y + w->h);
	glEnd();
	draw_border(w->x, w->y, w->w, w->h);


	if (w->state != WSTATE_EDITING) {
		glBegin(GL_QUADS);
			switch (w->state) {
				case WSTATE_NORMAL:
				case WSTATE_HOVERED: glColor3f(COLOR_WRANGE_SLIDER1); break;
				case WSTATE_PRESSED: glColor3f(COLOR_WRANGE_SLIDER2); break;
				default: break;
			}
			glVertex2f(w->x + map(w->value, w->min, w->max, 0, w->w), w->y);
			glVertex2f(w->x, w->y);

			switch (w->state) {
				case WSTATE_NORMAL:
				case WSTATE_HOVERED: glColor3f(COLOR_WRANGE_SLIDER2); break;
				case WSTATE_PRESSED: glColor3f(COLOR_WRANGE_SLIDER1); break;
				default: break;
			}
			glVertex2f(w->x, w->y + w->h);
			glVertex2f(w->x + map(w->value, w->min, w->max, 0, w->w), w->y + w->h);
		glEnd();

		switch (w->state) {
			case WSTATE_NORMAL:  glColor3f(COLOR_WRANGE_NORMAL3);  break;
			case WSTATE_HOVERED: glColor3f(COLOR_WRANGE_HOVERED3); break;
			case WSTATE_PRESSED: glColor3f(COLOR_WRANGE_PRESSED3); break;
			default: break;
		}
		char buf[20];
		snprintf(buf, 19, "%g", w->value);
		draw_string_centered(w->x + w->w/2, w->y + (w->h-16)/2, w->w, buf, 0);
	}
	else {
		glColor3f(COLOR_WRANGE_PRESSED3);
		draw_string(w->x+10, w->y + (w->h-16)/2, w->w-20, buf_editing, 0);
		float t = w->x + 12 + strlen(buf_editing)*8;
		glColor3f(COLOR_WRADIO_PRESSED1);
		glLineWidth(2);
		glBegin(GL_LINES);
			glVertex2f(t, w->y+2);
			glVertex2f(t, w->y+w->h-4);
		glEnd();
	}
}

void wrange_click(WRange * w, int button, int state, int x, int y)
{
	if (button == MOUSE_LEFT && state == MOUSE_DOWN)
		if (w->state == WSTATE_HOVERED) {
			w->tmpx = x;
			w->tmpf = w->value;
			w->state = WSTATE_PRESSED;
			hook(w, (ClickFunc)&wrange_click, (DragFunc)&wrange_drag,
				NULL, (KeyFunc)&wrange_key);
		}

	if (button == MOUSE_LEFT && state == MOUSE_UP)
		if (hooked == w) {
			if (w->state != WSTATE_EDITING) {
				if (x == w->tmpx) {
					snprintf(buf_editing, 19, "%g", w->value);
					w->state = WSTATE_EDITING;
				}
				else {
					unhook();
					w->state = WSTATE_NORMAL;
					wrange_hover(w, x, y);
				}
			}
			else if (!hovertest_box(x, y, w->x, w->y, w->w, w->h))
				wrange_key(w, '\r');
		}

	if (button == MOUSE_RIGHT && state == MOUSE_UP)
		if (hooked == w) {
			if (w->state != WSTATE_EDITING) {
				unhook();
				w->value = w->tmpf;
				w->state = WSTATE_NORMAL;
				wrange_hover(w, x, y);
			}
			else if (!hovertest_box(x, y, w->x, w->y, w->w, w->h))
				wrange_key(w, '\e');
		}
}

void wrange_drag(WRange * w, int x, int y)
{
	if (w->state == WSTATE_EDITING) return;
	float t = w->tmpf + map(x - w->tmpx, 0, w->w, 0, w->max - w->min);
	t = STEP(t, w->step);
	w->value = CLAMP(t, w->min, w->max);
}

void wrange_hover(WRange * w, int x, int y)
{
	if (hovertest_box(x, y, w->x, w->y, w->w, w->h))
		w->state = WSTATE_HOVERED;
	else
		w->state = WSTATE_NORMAL;
}

void wrange_key(WRange * w, unsigned char k)
{
	if (w->state == WSTATE_EDITING) {
		if ((k >= '0' && k <= '9') || k == '.' || k == '-') {
			int len = strlen(buf_editing);
			if (len < 20) {
				buf_editing[len+1] = 0;
				buf_editing[len]   = k;
			}
		}
		else if (k == '\b') {
			if (buf_editing[0]) buf_editing[strlen(buf_editing)-1] = 0;
		}
		else if (k == '\r') {
			float t;
			if (!sscanf(buf_editing, "%g", &t))
				t = w->min;
			t = STEP(t, w->step);
			w->value = CLAMP(t, w->min, w->max);
			w->state = WSTATE_NORMAL;
			unhook();
		}
		else if (k == '\e') {
			w->state = WSTATE_NORMAL;
			unhook();
		}
	}
	else {
		if (k == '\r') {
			w->state = WSTATE_NORMAL;
			unhook();
		}
		else if (k == '\e') {
			w->value = w->tmpf;
			w->state = WSTATE_NORMAL;
			unhook();
		}
	}
}

