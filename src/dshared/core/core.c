
/************************************************************
 * dewox: core.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "core.h"

int d_playing = 0;
int d_playing_time = 0;

static int start_time;

inline void d_play(long ticks)
{
	start_time = ticks - d_playing_time;
	d_playing = 1;
}

inline void d_stop()
{
	d_playing = 0;
}

inline void d_refresh(long ticks)
{
	if (d_playing)
		d_playing_time = ticks - start_time;
}

