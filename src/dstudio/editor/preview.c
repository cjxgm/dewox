
/************************************************************
 * dewox: preview
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"

static UIMenu menu[] = {
	{UI_MENU_DONE}
};

void editor_preview_init()
{
	REGISTER_EDITOR("Preview");
}

static void render(int w, int h)
{
	float logosize[2];
	d_logo_get_size(&logosize[0], &logosize[1]);
	d_logo_draw_init((w-logosize[0]) / 2.0f,
					 (h-logosize[1]) / 2.0f,
					 1, d_playing_time);

	glPointSize(1.0f);
	glColor3f(1.0f, 0.5f, 0.2f);
	font_render("No Content", 20, 20);
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

