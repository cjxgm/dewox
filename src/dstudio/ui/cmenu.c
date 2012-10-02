
/************************************************************
 * dewox: cmenu.c
 * Chained Menu
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "cmenu.h"
#include "ui.h"
#include "../config.h"
#include "../wm.h"
#include "../../dshared/dshared.h"
#include <GL/gl.h>
#include <string.h>


static CMenuSub * cmenu_sub_create();
static void cmenu_push(CMenu * menu, CMenuSub * sub);

void cmenu_render(int w, int h);
void cmenu_hover(int x, int y, int w, int h);
void cmenu_click(int x, int y, int w, int h, int btn, int stt);
void cmenu_keypress(int key, int w, int h);

static CMenu * cmenu;
static float cmenu_x;
static float cmenu_y;
static float cmenu_w;
static float cmenu_h;
static int start_time;
static int is_back;



// external functions

CMenu * cmenu_create()
{
	CREATE(CMenu, menu);
	menu->sub  = cmenu_sub_create();
	menu->sp   = -1;
	return menu;
}

void * cmenu_sub_add(CMenuSub * sub, const char * name, int key,
		CMenuCallback * callback, void * data)
{
	if (!callback && !data) data = cmenu_sub_create();

	CMenuItem * item = &sub->items[sub->size++];
	item->name     = name;
	item->key      = key;
	item->callback = callback;
	item->data     = data;

	int w = font_width(name) + 10;
	if (w > sub->w) sub->w = w;

	return data;
}

void cmenu_show(CMenu * menu, float x, float y)
{
	cmenu   = menu;
	cmenu_x = x;
	cmenu_y = y;
	cmenu_w = cmenu_h = 0;
	start_time = wm_ticks();
	is_back = 0;

	cmenu_push(menu, menu->sub);
	wm_capture(menu, cmenu_render, cmenu_hover,
			cmenu_click, NULL, cmenu_keypress);
	wm_require_refresh();
}

CMenuItem * cmenu_sub_find(CMenuSub * sub, const char * name)
{
	int i;
	for (i=0; i<sub->size; i++)
		if (!strcmp(sub->items[i].name, name))
			return &sub->items[i];
	return NULL;
}



// internal functions

static CMenuSub * cmenu_sub_create()
{
	CREATE(CMenuSub, sub);
	sub->size = 0;
	sub->w    = 0;
	return sub;
}


static void cmenu_push(CMenu * menu, CMenuSub * sub)
{
	CMenuStack * s = &menu->stack[++menu->sp];
	s->sub      = sub;
	s->selected = -1;
}




// rendering & events

void cmenu_render(int w, int h)
{
	float dw = 0;
	float dh = 0;
	float dx = cmenu_x;
	float dy = cmenu_y;
	int i;

	for (i=cmenu->sp; i>=0; i--) {
		dw += cmenu->stack[i].sub->w;
		if (i != cmenu->sp) dx -= cmenu->stack[i].sub->w;
		if (cmenu->stack[i].sub->size > dh)
			dh = cmenu->stack[i].sub->size;
	}
	dw += 20;	// for shortcut keys
	dh *= 20;
	dh += 20;	// for "Back" button

	float t = wm_ticks() - start_time;
	if (t < CMENU_SPEED) {
		dx = ferp_out(t, 0, CMENU_SPEED, cmenu_x, dx);
		dw = ferp_out(t, 0, CMENU_SPEED, cmenu_w, dw);
		dh = ferp_out(t, 0, CMENU_SPEED, cmenu_h, dh);
		wm_require_refresh();
	}
	else {
		start_time = wm_ticks() - CMENU_SPEED;
		cmenu_x = dx;	// FIXME
		cmenu_w = dw;
		cmenu_h = dh;
		t = CMENU_SPEED;
	}

	glColor4f(0, 0, 0, 0.8f);
	glRectf(dx-8, dy-8, dx+dw+8, dy+dh+8);
	draw_outline(dx-8, dy-8, dw+16, dh+16);

	dx = ferp_out(t, 0, CMENU_SPEED, 20, 0) + cmenu_x;
	glColor4f(0, 0, 0, ferp_out(t, 0, CMENU_SPEED, 0, 1));

	for (i=cmenu->sp; i>=0; i--) {
		CMenuSub * sub = cmenu->stack[i].sub;
		float tx;
		if (i == cmenu->sp) tx = dx + 20;	// skip shortcut keys
		else tx = dx - sub->w;		// FIXME
		int j;
		for (j=0; j<sub->size; j++) {
			draw_button(tx, dy+j*20, sub->w, 18,
					(cmenu->stack[cmenu->sp].selected == j ?
							 UI_BUTTON_STATE_ACTIVE : 
							 UI_BUTTON_STATE_NORMAL));
			font_render(sub->items[i].name, tx+5, dy+j*20);
		}
	}
	draw_button(dx + 20, dy+dh-20, font_width("Back")+10, 18,
			(cmenu->stack[cmenu->sp].selected == -2 ?
					 UI_BUTTON_STATE_ACTIVE : 
					 UI_BUTTON_STATE_NORMAL));
	font_render("Back", dx+20+5, dy+dh-20);
}

void cmenu_hover(int x, int y, int w, int h)
{
	float dw = cmenu_w;
	float dh = cmenu_h;
	float dx = cmenu_x;
	float dy = cmenu_y;
	if (is_in_box(x, y, dx+20, dy+dh-20, dx+dw, dy+dh-2))
		cmenu->stack[cmenu->sp].selected = -2;
	else {
		if (is_in_box(x, y, dx+20, dy, dx+dw, dy+dh-20))
			cmenu->stack[cmenu->sp].selected = (y-dy)/20;
	}

	wm_require_refresh();		// FIXME: Do not always refresh
}

void cmenu_click(int x, int y, int w, int h, int btn, int stt)
{
	if (btn != WM_BUTTON_LEFT)
		return;

	if (stt == WM_BUTTON_UP) {
		int selected = cmenu->stack[cmenu->sp].selected;
		if (selected == -2) {
			cmenu->sp = -1;		// TODO
			wm_uncapture();
		}
		else if (selected >= 0) {
			CMenuItem * item =
					&cmenu->stack[cmenu->sp].sub->items[selected];
			if (!item->callback) {
				cmenu_push(cmenu, item->data);
				start_time = wm_ticks();
			}
			else {	// TODO
			}
		}
		wm_require_refresh();
	}
}

void cmenu_keypress(int key, int w, int h)
{
}

