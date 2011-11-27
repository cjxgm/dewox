
#include <GL/gl.h>
#include "button.h"
#include "../window.h"
#include "../config.h"
#include "../event.h"
#include "../font.h"

void wbutton_draw(WButton * w)
{
	glBegin(GL_QUADS);
		switch (w->state) {
			case WSTATE_NORMAL:  glColor3f(COLOR_WBUTTON_NORMAL1);  break;
			case WSTATE_HOVERED: glColor3f(COLOR_WBUTTON_HOVERED1); break;
			case WSTATE_PRESSED: glColor3f(COLOR_WBUTTON_PRESSED1); break;
			default: break;
		}
		glVertex2f(w->x + w->w, w->y);
		glVertex2f(w->x, w->y);

		switch (w->state) {
			case WSTATE_NORMAL:  glColor3f(COLOR_WBUTTON_NORMAL2);  break;
			case WSTATE_HOVERED: glColor3f(COLOR_WBUTTON_HOVERED2); break;
			case WSTATE_PRESSED: glColor3f(COLOR_WBUTTON_PRESSED2); break;
			default: break;
		}
		glVertex2f(w->x, w->y + w->h);
		glVertex2f(w->x + w->w, w->y + w->h);
	glEnd();

	switch (w->state) {
		case WSTATE_NORMAL:  glColor3f(COLOR_WBUTTON_NORMAL3);  break;
		case WSTATE_HOVERED: glColor3f(COLOR_WBUTTON_HOVERED3); break;
		case WSTATE_PRESSED: glColor3f(COLOR_WBUTTON_PRESSED3); break;
		default: break;
	}
	draw_string_centered(w->x + w->w/2, w->y + (w->h-16)/2, w->w,
							w->label, 0);
	draw_border(w->x, w->y, w->w, w->h);
}

void wbutton_click(WButton * w, int button, int state, int x, int y)
{
	if (button == MOUSE_LEFT && state == MOUSE_DOWN)
		if (w->state == WSTATE_HOVERED) {
			w->state = WSTATE_PRESSED;
			hook(w, (ClickFunc)&wbutton_click, (DragFunc)&wbutton_drag, NULL, NULL);
		}

	if (button == MOUSE_LEFT && state == MOUSE_UP)
		if (hooked == w) {
			unhook();
			w->clicked = (w->state == WSTATE_PRESSED);
			w->state = (w->clicked ? WSTATE_HOVERED : WSTATE_NORMAL);
		}
}

void wbutton_drag(WButton * w, int x, int y)
{
	if (hovertest_box(x, y, w->x, w->y, w->w, w->h))
		w->state = WSTATE_PRESSED;
	else
		w->state = WSTATE_NORMAL;
}


void wbutton_hover(WButton * w, int x, int y)
{
	if (hovertest_box(x, y, w->x, w->y, w->w, w->h))
		w->state = WSTATE_HOVERED;
	else
		w->state = WSTATE_NORMAL;
}

