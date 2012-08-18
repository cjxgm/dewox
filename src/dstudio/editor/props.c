
/************************************************************
 * dewox: props
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"
#include <stdio.h>

static DParam * config;
static DParamMeta config_meta[] = {
	{D_TYPE_FLOAT, "hello", 0.5, 0.0, 1.0, 0.1},
	{D_TYPE_FLOAT, "hhasjdhsjd", 0.1, 0.0, 1.0, 0.01},
	{D_TYPE_FLOAT, "hhaasdjdgdgo", 0.2, 0.0, 1.0, 0.1},
	{D_TYPE_DONE}
};

static void config_cb();

static UIMenu menu[] = {
	{UI_MENU_BUTTON, &config_cb, "#"},
	{UI_MENU_DONE}
};

void editor_props_init()
{
	REGISTER_EDITOR("Properties");
	config = d_create_param_from_meta(config_meta);
}

static void render(int w, int h)
{
	static char buf[32];
	if (!d_active_param) return;
	
	DParam * p = d_active_param;
	float maxw = 0;
	while (p->meta->type) {
		float w = font_width(p->meta->name);
		if (w > maxw) maxw = w;
		p++;
	}
	maxw += 20;

	glPointSize(1);
	p = d_active_param;
	while (p->meta->type) {
		float y = h-10 - 20 - (p-d_active_param)*20;

		glColor3f(0.2, 0.8, 0.2);
		font_render(p->meta->name, 10, y);

		sprintf(buf, "%g", p->f);
		draw_button(maxw, y, w-maxw-10, 18, UI_BUTTON_STATE_NORMAL);
		glColor3f(1.0, 1.0, 1.0);
		font_renderw(buf, maxw+10, y, w-maxw-30);
		p++;
	}
}

static void hover(int x, int y, int w, int h)
{
}

static void click(int x, int y, int w, int h, int btn, int stt)
{
}

static void drag(int x, int y, int w, int h)
{
}

static void keypress(int key, int w, int h)
{
}

////////////////////////////////////////
//
// callbacks
//

static void config_cb()
{
	d_active_param = config;
}

