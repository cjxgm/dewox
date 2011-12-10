
#include <GL/gl.h>
#include "radio.h"
#include "window.h"
#include "config.h"
#include "event.h"
#include "font.h"

static void draw_radio_button(float x, float y, float w, float h,
								const char * label, WState state)
{
	glBegin(GL_QUADS);
		switch (state) {
			case WSTATE_NORMAL:  glColor3f(COLOR_WRADIO_NORMAL1);  break;
			case WSTATE_HOVERED: glColor3f(COLOR_WRADIO_HOVERED1); break;
			case WSTATE_PRESSED: glColor3f(COLOR_WRADIO_PRESSED1); break;
			default: break;
		}
		glVertex2f(x + w, y);
		glVertex2f(x, y);

		switch (state) {
			case WSTATE_NORMAL:  glColor3f(COLOR_WRADIO_NORMAL2);  break;
			case WSTATE_HOVERED: glColor3f(COLOR_WRADIO_HOVERED2); break;
			case WSTATE_PRESSED: glColor3f(COLOR_WRADIO_PRESSED2); break;
			default: break;
		}
		glVertex2f(x, y + h);
		glVertex2f(x + w, y + h);
	glEnd();

	switch (state) {
		case WSTATE_NORMAL:  glColor3f(COLOR_WRADIO_NORMAL3);  break;
		case WSTATE_HOVERED: glColor3f(COLOR_WRADIO_HOVERED3); break;
		case WSTATE_PRESSED: glColor3f(COLOR_WRADIO_PRESSED3); break;
		default: break;
	}
	draw_string_centered(x + w/2, y + (h-16)/2, w,
							label, 0);
	draw_border(x, y, w, h);
}

void wradio_draw(WRadio * w)
{
	int n = 0;
	while (w->items[n]) n++;
	if (!n) return;

	float we = w->w / (float)n;		// w[idth] e[ach]

	if (we < 10.0f) {
		if (we > 0) draw_border(w->x, w->y, w->w, w->h);
		return;
	}

	int i;
	for (i=0; w->items[i]; i++)
		draw_radio_button(w->x + i*we, w->y, we, w->h,
				w->items[i], (i==w->selected ? WSTATE_PRESSED :
								(i==w->tmp ? w->state: WSTATE_NORMAL)));
}

void wradio_click(WRadio * w, int button, int state, int x, int y)
{
	if (button == MOUSE_LEFT && state == MOUSE_DOWN)
		if (w->state == WSTATE_HOVERED) {
			w->selected = w->tmp;
			hook(w, (ClickFunc)&wradio_click, NULL, NULL, NULL);
		}

	if (button == MOUSE_LEFT && state == MOUSE_UP)
		if (hooked == w)
			unhook();
}

void wradio_hover(WRadio * w, int x, int y)
{
	int n = 0;
	while (w->items[n]) n++;
	if (!n) return;

	w->state = WSTATE_NORMAL;

	float we = w->w / (float)n;		// w[idth] e[ach]

	if (we < 10.0f) return;

	int i;
	for (i=0; i<n; i++) {
		if (i == w->selected) continue;
		if (hovertest_box(x, y, w->x + i*we, w->y, we, w->h)) {
			w->tmp = i;
			w->state = WSTATE_HOVERED;
			break;
		}
	}
}

