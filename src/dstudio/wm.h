
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

#include <GL/glut.h>

// mouse buttons
#define WM_BUTTON_LEFT		GLUT_LEFT_BUTTON
#define WM_BUTTON_RIGHT		GLUT_RIGHT_BUTTON
#define WM_BUTTON_MID		GLUT_MIDDLE_BUTTON
// mouse states
#define WM_BUTTON_UP		GLUT_UP
#define WM_BUTTON_DOWN		GLUT_DOWN
// modifier key masks
#define WM_MOD_SHIFT		GLUT_ACTIVE_SHIFT
#define WM_MOD_CTRL			GLUT_ACTIVE_CTRL
#define WM_MOD_ALT			GLUT_ACTIVE_ALT
#define WM_MOD_SC			(WM_MOD_SHIFT | WM_MOD_CTRL)
#define WM_MOD_SA			(WM_MOD_SHIFT | WM_MOD_ALT )
#define WM_MOD_CA			(WM_MOD_CTRL  | WM_MOD_ALT )
#define WM_MOD_SCA			(WM_MOD_SC    | WM_MOD_CA  )




// FIXME: Prefix 'WM' to all these types
typedef void (EditorRenderFunc)(int w, int h);
typedef void (EditorHoverFunc)(int x, int y, int w, int h);
typedef void (EditorClickFunc)(int x, int y, int w, int h,
		int btn, int stt);	// btn=button, stt=state
typedef void (EditorDragFunc)(int x, int y, int w, int h);
typedef void (EditorKeypressFunc)(int key, int w, int h);
typedef struct EditorInfo
{
	const char * name;
	// FIXME: Prefix 'const' to them
	EditorRenderFunc	* render;
	EditorHoverFunc		* hover;
	EditorClickFunc		* click;
	EditorDragFunc		* drag;
	EditorKeypressFunc	* keypress;
}
EditorInfo;
typedef EditorInfo CaptureInfo;




extern int wm_win_w;
extern int wm_win_h;

extern int wm_editor_cnt;

inline void wm_init();
inline void wm_mainloop();
inline void wm_require_refresh();
inline int  wm_ticks();		// get ticks (1 tick = 1 millisecond)
inline int  wm_mods();		// get modifier keys
inline int  wm_active_win_x();		// get active window's x
inline int  wm_active_win_y();		// get active window's y

inline EditorInfo * wm_get_editor(int id);
void wm_register_editor(const char * name,
		EditorRenderFunc * render, EditorHoverFunc * hover,
		EditorClickFunc * click, EditorDragFunc * drag,
		EditorKeypressFunc * keypress);
void wm_capture(void * data,
		EditorRenderFunc * render, EditorHoverFunc * hover,
		EditorClickFunc * click, EditorDragFunc * drag,
		EditorKeypressFunc * keypress);
inline void wm_uncapture();
inline void * wm_capdata();	// get the data passed to wm_capture

#endif

