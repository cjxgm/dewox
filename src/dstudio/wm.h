
/************************************************************
 * dewox: wm.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __WM_H
#define __WM_H

typedef void (EditorRenderFunc)(int w, int h);
typedef struct EditorInfo
{
	const char * name;
	EditorRenderFunc * render;
}
EditorInfo;




extern int wm_win_w;
extern int wm_win_h;

extern int wm_editor_cnt;

inline void wm_init();
inline void wm_mainloop();
inline void wm_require_refresh();
inline int  wm_ticks();

inline EditorInfo * wm_get_editor(int id);
void wm_register_editor(const char * name, EditorRenderFunc * render);

#endif

