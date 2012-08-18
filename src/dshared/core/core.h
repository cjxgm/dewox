
/************************************************************
 * dewox: core.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __D_CORE_H
#define __D_CORE_H

#include <stdlib.h>

#define NEW(T)					malloc(sizeof(T))
#define CREATE(T, N)			T * N = NEW(T)
#define NEW2(T, C)				calloc(sizeof(T), (C))
#define CREATE2(T, N, C)		T * N = NEW2(T, C)

#ifndef NULL
# define NULL  					((void *)0)
#endif

extern int d_playing;
extern int d_playing_time;

inline void d_play();
inline void d_stop();
inline void d_refresh();

#endif
