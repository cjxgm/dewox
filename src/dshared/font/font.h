
/************************************************************
 * dewox: font.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __D_FONT_H
#define __D_FONT_H

void font_render(const char * str, int x, int y);
void font_renderw(const char * str, int x, int y, float w);
int font_width(const char * str);

#endif

