
#include <GL/gl.h>
#include <stdlib.h>
#include "radio.h"
#include "button.h"
#include "../window.h"
#include "../event.h"

void wradio_new(WRadio * w, WRadioEntry entries[])
{
	for (w->btn_cnt=0; entries[w->btn_cnt]; w->btn_cnt++) {}
	w->btns = calloc(sizeof(WRadio), w->btn_cnt);
	
	int i;
	for (i=0; i<w->btn_cnt; i++) {
		w->btns[i].label = entries[i];
		w->btns[i].x = w->x + i * w->w / w->btn_cnt;
		w->btns[i].y = w->y;
		w->btns[i].w = w->w / w->btn_cnt;
		w->btns[i].h = w->h;
	}
	w->btns[w->selected].state = WSTATE_SELECTED;
}

void wradio_draw(WRadio * w)
{
	int i;
	for (i=0; i<w->btn_cnt; i++) {
		if (w->btns[i].clicked) {
			w->btns[i].clicked = 0;
			w->btns[w->selected].state = WSTATE_NORMAL;
			w->selected = i;
			w->btns[i].state = WSTATE_SELECTED;
		}
		wbutton_draw(&w->btns[i]);
	}
}

void wradio_click(WRadio * w, int button, int state, int x, int y)
{
	int i;
	for (i=0; i<w->btn_cnt; i++)
		if (i != w->selected)
			wbutton_click(&w->btns[i], button, state, x, y);
}

void wradio_drag(WRadio * w, int x, int y)
{
	int i;
	for (i=0; i<w->btn_cnt; i++)
		if (i != w->selected)
			wbutton_drag(&w->btns[i], x, y);
}

void wradio_hover(WRadio * w, int x, int y)
{
	int i;
	for (i=0; i<w->btn_cnt; i++)
		if (i != w->selected)
			wbutton_hover(&w->btns[i], x, y);
}

