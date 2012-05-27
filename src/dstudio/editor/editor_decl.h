
/************************************************************
 * dewox: editor_decl.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

// NOTE: This file can only be, and must be, included by an editor!

#ifndef __EDITOR_DECL_H
#define __EDITOR_DECL_H

#include "../wm.h"
#include <GL/gl.h>

#define REGISTER_EDITOR(NAME) \
	wm_register_editor(NAME, render, hover, click, drag, keypress);

static void render(int w, int h);
static void hover(int x, int y, int w, int h);
static void click(int x, int y, int w, int h, int btn, int stt);
static void drag(int x, int y, int w, int h);
static void keypress(int key, int w, int h);

#endif

