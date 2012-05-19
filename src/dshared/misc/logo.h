
/************************************************************
 * dewox: logo.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __D_LOGO_H
#define __D_LOGO_H

void d_logo_draw(float x, float y);
// when stage == 0, param is the percentage of loading progress
// when stage == 1, param is the time in milliseconds
// when animation done, return 1.
int d_logo_draw_init(float x, float y, int stage, int param);
void d_logo_get_size(float * w, float * h);

#endif

