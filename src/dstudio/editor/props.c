
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

static DParam * scene_setup;
static DParamMeta scene_setup_meta[] = {
	{D_TYPE_FLOAT, "Test", 1.0, 0.0, 3.0, 0.1},
	{D_TYPE_FLOAT, "Test2", 1.4, 0.0, 3.0, 0.1},
	{D_TYPE_FLOAT, "Hi", 1.3, 0.0, 3.0, 0.1},
	{D_TYPE_DONE}
};

static void scene_setup_cb();
static UIMenu menu[] = {
	{UI_MENU_BUTTON, &scene_setup_cb, "Scene Setup"},
	{UI_MENU_DONE}
};

void editor_props_init()
{
	REGISTER_EDITOR("Properties");
	scene_setup = d_create_param_from_meta(scene_setup_meta);
}

static void render(int w, int h)
{
	char buf[64];
	DParam * p;

	if (d_active_param) {
		glColor3f(0.2, 1.0, 0.5);
		glPointSize(1);
		p = d_active_param;
		while (p->meta->type) {
			sprintf(buf, "%s: %g", p->meta->name, p->f);
			font_render(buf, 30, (p-d_active_param)*20 + 20);
			p++;
		}
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

static void scene_setup_cb()
{
	d_active_param = scene_setup;
}

