
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



// external functions

CMenu * cmenu_create()
{
	CREATE(CMenu, menu);
	menu->sub  = cmenu_sub_create();
	menu->sp   = -1;
	menu->w    = 0.0f;
	menu->h    = 0.0f;
	menu->neww = 0.0f;
	menu->newh = 0.0f;
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

	int w = font_width(name);
	if (w > sub->w) sub->w = w;

	return data;
}

void cmenu_show(CMenu * menu, float x, float y)
{
	cmenu   = menu;
	cmenu_x = x;
	cmenu_y = y;

	menu->w = menu->h = 0;
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
	glColor4f(1, 1, 1, 0.8f);
	glRectf(cmenu_x, cmenu_y, cmenu_x+100, cmenu_y+100);
}

void cmenu_hover(int x, int y, int w, int h)
{
}

void cmenu_click(int x, int y, int w, int h, int btn, int stt)
{
}

void cmenu_keypress(int key, int w, int h)
{
}

