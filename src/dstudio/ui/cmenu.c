
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

	return data;
}

void cmenu_show(CMenu * menu, float x, float y)
{
}

CMenuItem * cmenu_sub_find(CMenuSub * sub, const char * name)
{
	int i;
	for (i=0; i<sub->size; i++)
		if (!strcmp(sub->items[i].name, name))
			return &sub->items[i];
	return NULL;
}




static CMenuSub * cmenu_sub_create()
{
	CREATE(CMenuSub, sub);
	sub->size = 0;
	sub->w    = 0;
	return sub;
}

