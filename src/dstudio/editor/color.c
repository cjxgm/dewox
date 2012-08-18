
/************************************************************
 * dewox: color
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"

static DParam * config;
static DParamMeta config_meta[] = {
	{D_TYPE_COLOR, "background", 0.8, 0.5, 0.2},
	{D_TYPE_DONE}
};

static void config_cb();

static UIMenu menu[] = {
	{UI_MENU_BUTTON, &config_cb, "#"},
	{UI_MENU_DONE}
};

void editor_color_init()
{
	REGISTER_EDITOR("Color");
	config = d_create_param_from_meta(config_meta);
}

static void render(int w, int h)
{
	glColor3f(config[0].v[0], config[0].v[1], config[0].v[2]);
	glRectf(0, 0, w, h);
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

