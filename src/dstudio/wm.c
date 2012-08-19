
/************************************************************
 * dewox: wm.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "wm.h"
#include "config.h"
#include "../dshared/dshared.h"
#include "editor/editor.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int wm_win_w = 640;
int wm_win_h = 480;

// for init animation
static int stage = 0;
static int init_percent = 0;
static int init_percent_current = 0;

#define MODE_EDGE_SELECTED		1
#define MODE_WIN_CLOSING		2
#define MODE_WIN_SPLIT_Y		3
#define MODE_WIN_SPLIT_X		4
static int mode = 0;
static int edge = 0;
static int edge_x = 0;
static int edge_y = 0;
static int edge_w = 0;
static int edge_h = 0;
static int active_win = 0;
static int win_x = 0;
static int win_y = 0;
static int win_w = 0;
static int win_h = 0;
static float win_close_ratio = 0;
static int win_close_ticks = 0;


static void close_cb();
static void split_y_cb();
static void split_x_cb();
static UIMenu wm_menu[] = {
	{UI_MENU_FUNC, &close_cb,   "X"},
	{UI_MENU_FUNC, &split_y_cb, "-"},
	{UI_MENU_FUNC, &split_x_cb, "|"},
	{UI_MENU_EDITOR_SELECTOR},
	{UI_MENU_SUBMENU},
	{UI_MENU_DONE}
};

// events
static void idle();
static void resize(int w, int h);
static void hover(int mx, int my);
static void click(int btn, int stt, int mx, int my);
static void drag(int mx, int my);
static void keypress(unsigned char key, int x, int y);

// window management
#define WINDOW_TYPE_UNUSED		0
#define WINDOW_TYPE_SPLIT_X		1
#define WINDOW_TYPE_SPLIT_Y		2
#define EDGE_FLAG_NONE			0
#define EDGE_FLAG_DRAW			1
static struct WindowInfo
{
	int type;
	int child[2];
	float ratio;
	int edge_flag;
	UIMenuParam menu_param;
} windows[WM_MAX_WINDOW_CNT];

static EditorInfo editors[WM_MAX_EDITOR_CNT];
int wm_editor_cnt = 0;

static CaptureInfo cap;

static int alloc_win();
static void free_win(int win);
static void close_win();
static void split_win(int type, float ratio);

// some useful functions
static void render(int win, int x, int y, int w, int h);
static void view2d(int x, int y, int w, int h);

// threads
static pthread_t thread_id_init;
static void * thread_init(void * __unused__);

////////////////////////////////////////
//
// externals
//

inline void wm_init()
{
	// init glut
	int argc = 1;
	char * argv[] = {"dstudio"};	// this sucks!!!
	glutInit(&argc, argv);

	// create render window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(wm_win_w, wm_win_h);
	glutCreateWindow("Dewox");

	// bind events
	glutDisplayFunc(&wm_require_refresh);
	glutReshapeFunc(&resize);

	// setup blank color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// setup anti-aliasing for points and lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// init windows
	int i;
	for (i=0; i<WM_MAX_EDITOR_CNT; i++) {
		//windows[i].type   = WINDOW_TYPE_UNUSED;
		//windows[i].edge_flag = EDGE_FLAG_NONE;
		windows[i].child[0] = i + 1;
		windows[i].menu_param.active = -1;
	}
	windows[WM_MAX_WINDOW_CNT-1].child[0] = 0;

	// register internal editors
	wm_register_editor("unused" , NULL, NULL, NULL, NULL, NULL, NULL);
	wm_register_editor("split-x", NULL, NULL, NULL, NULL, NULL, NULL);
	wm_register_editor("split-y", NULL, NULL, NULL, NULL, NULL, NULL);
	// register external editors
	editor_init();

	// create a window
	int win = alloc_win();
	windows[win].type = 3;	// the first external editor
}

inline void wm_mainloop()
{
#ifdef WM_FULLSCREEN
	glutFullScreen();
#endif
	glutMainLoop();
}

inline void wm_require_refresh()
{
	glutIdleFunc(&idle);
}

inline int wm_ticks()
{
	return glutGet(GLUT_ELAPSED_TIME);
}

inline int wm_mods()
{
	return glutGetModifiers();
}

inline int wm_active_win_x()
{
	return win_x;
}

inline int wm_active_win_y()
{
	return win_y;
}

inline EditorInfo * wm_get_editor(int id)
{
	return &editors[id];
}

void wm_register_editor(const char * name, UIMenu * menu,
		EditorRenderFunc * render, EditorHoverFunc * hover,
		EditorClickFunc * click, EditorDragFunc * drag,
		EditorKeypressFunc * keypress)
{
	editors[wm_editor_cnt].name		= name;
	editors[wm_editor_cnt].menu		= menu;
	editors[wm_editor_cnt].render	= render;
	editors[wm_editor_cnt].hover	= hover;
	editors[wm_editor_cnt].click	= click;
	editors[wm_editor_cnt].drag		= drag;
	editors[wm_editor_cnt].keypress	= keypress;
	wm_editor_cnt++;
}

void wm_capture(void * data,
		EditorRenderFunc * render, EditorHoverFunc * hover,
		EditorClickFunc * click, EditorDragFunc * drag,
		EditorKeypressFunc * keypress)
{
	cap.name	 = data;	// 'name' is just a pointer
	cap.render	 = render;
	cap.hover	 = hover;
	cap.click	 = click;
	cap.drag	 = drag;
	cap.keypress = keypress;
}

inline void wm_uncapture()
{
	cap.name = NULL;
}

inline void * wm_capdata()
{
	return (void *)cap.name;
}

////////////////////////////////////////
//
// events
//

static void idle()
{
	float logosize[2];
	static long logotime = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (stage) {
		case 0: // start init thread
			pthread_create(&thread_id_init, PTHREAD_CREATE_JOINABLE, &thread_init, NULL);
			stage++;
			break;
		case 1: // draw init animation
			if (init_percent_current < init_percent)
				init_percent_current++;
			d_logo_get_size(&logosize[0], &logosize[1]);
			if (init_percent_current == 100) {
				logotime = wm_ticks();
				init_percent_current++;
			}
			view2d(0, 0, wm_win_w, wm_win_h);
			if (d_logo_draw_init((wm_win_w-logosize[0]) / 2.0f,
								 (wm_win_h-logosize[1]) / 2.0f,
								 (init_percent_current > 100),
									(init_percent_current <= 100 ?
									 init_percent_current :
									 wm_ticks() - logotime)))
				stage++;
			break;
		case 2: // data init done, init events
			glutPassiveMotionFunc(&hover);
			glutMotionFunc(&drag);
			glutMouseFunc(&click);
			glutKeyboardFunc(&keypress);
			stage++;
			break;
		case 3: // events init done, render UI
			glutIdleFunc(NULL);
			render(1, 0, 0, wm_win_w, wm_win_h);
			if (wm_capdata() && cap.render) {
				view2d(0, 0, wm_win_w, wm_win_h);
				// no need for specifying width and height, so set to 0.
				cap.render(0, 0);
			}
			if (d_time_changed) d_time_changed--;
			break;
	}
	glutSwapBuffers();
}

static void resize(int w, int h)
{
	wm_win_w = w;
	wm_win_h = h;

	active_win = 0;
	edge = 0;
}

static void hover(int mx, int my)
{
	if (mode == MODE_WIN_CLOSING) return;

	my = wm_win_h - my;

	if (mode == MODE_WIN_SPLIT_Y) {
		edge_y = my - win_y;
		wm_require_refresh();
		return;
	}
	if (mode == MODE_WIN_SPLIT_X) {
		edge_x = mx - win_x;
		wm_require_refresh();
		return;
	}

	if (wm_capdata()) {
		if (cap.hover) cap.hover(mx, my, wm_win_w, wm_win_h);
		return;
	}

	// mouse event for edges
	int win = 1;
	int x = 0;
	int y = 0;
	int w = wm_win_w;
	int h = wm_win_h;
	int t;
	while (windows[win].type) {
		switch (windows[win].type) {
			case WINDOW_TYPE_SPLIT_X:
				edge = win;
				t = w * windows[win].ratio;
				if (mx >= x+t-2 && mx <= x+t+2) {
					if (windows[win].edge_flag != EDGE_FLAG_DRAW) {
						windows[win].edge_flag = EDGE_FLAG_DRAW;
						wm_require_refresh();
						mode = MODE_EDGE_SELECTED;
						edge_x = x;
						edge_w = w;
					}
					return;
				}
				else {
					if (windows[win].edge_flag != EDGE_FLAG_NONE) {
						windows[win].edge_flag = EDGE_FLAG_NONE;
						wm_require_refresh();
						mode = 0;
					}
					if (mx < x+t) {
						w = t;
						win = windows[win].child[0];
					}
					else if (mx > x+t) {
						x += t;
						w -= t;
						win = windows[win].child[1];
					}
					else win = 0;
				}
				break;
			case WINDOW_TYPE_SPLIT_Y:
				edge = win;
				t = h * windows[win].ratio;
				if (my >= y+t-2 && my <= y+t+2) {
					if (windows[win].edge_flag != EDGE_FLAG_DRAW) {
						windows[win].edge_flag = EDGE_FLAG_DRAW;
						wm_require_refresh();
						mode = MODE_EDGE_SELECTED;
						edge_y = y;
						edge_h = h;
					}
					return;
				}
				else {
					if (windows[win].edge_flag != EDGE_FLAG_NONE) {
						windows[win].edge_flag = EDGE_FLAG_NONE;
						wm_require_refresh();
						mode = 0;
					}
					if (my < y+t) {
						h = t;
						win = windows[win].child[0];
					}
					else if (my > y+t) {
						y += t;
						h -= t;
						win = windows[win].child[1];
					}
					else win = 0;
				}
				break;
			default:
				if (active_win != win) {
					if (active_win)
						windows[active_win].menu_param.active = -1;
					active_win = win;
					win_x = x;
					win_y = y;
					win_w = w;
					win_h = h;
					wm_require_refresh();
				}
				win = 0;
				break;
		}
	}

	// mouse event for window
	if (active_win) {
		if (my >= win_y + 25)
			editors[windows[active_win].type].hover(mx-win_x, my-win_y-25,
					win_w, win_h-25);
		else {
			// wm_menu[3] is the editor selector
			wm_menu[3].data = &windows[active_win].type;
			// wm_menu[4] is the sub menu of the editor
			wm_menu[4].data = editors[windows[active_win].type].menu;
			ui_menu_hover(wm_menu, &windows[active_win].menu_param,
					0, 0, mx-win_x, my-win_y);
			return;
		}
	}
}

static void click(int btn, int stt, int mx, int my)
{
	if (mode == MODE_WIN_CLOSING) return;

	my = wm_win_h - my;

	if (mode == MODE_WIN_SPLIT_Y) {
		if (btn == GLUT_LEFT_BUTTON && stt == GLUT_DOWN) {
			split_win(WINDOW_TYPE_SPLIT_Y, edge_y / (float)win_h);
			mode = 0;
			wm_require_refresh();
		}
		return;
	}
	if (mode == MODE_WIN_SPLIT_X) {
		if (btn == GLUT_LEFT_BUTTON && stt == GLUT_DOWN) {
			split_win(WINDOW_TYPE_SPLIT_X, edge_x / (float)win_w);
			mode = 0;
			wm_require_refresh();
		}
		return;
	}

	if (wm_capdata()) {
		if (cap.click) cap.click(mx, my, wm_win_w, wm_win_h, btn, stt);
		return;
	}

	if (mode == MODE_EDGE_SELECTED) return;

	if (active_win) {
		if (my >= win_y + 25)
			editors[windows[active_win].type].click(mx-win_x, my-win_y-25,
					win_w, win_h-25, btn, stt);
		else {
			// wm_menu[3] is the editor selector
			wm_menu[3].data = &windows[active_win].type;
			// wm_menu[4] is the sub menu of the editor
			wm_menu[4].data = editors[windows[active_win].type].menu;
			ui_menu_click(wm_menu, &windows[active_win].menu_param,
					0, 0, mx, my, btn, stt);
		}
	}
}

static void drag(int mx, int my)
{
	if (mode == MODE_WIN_CLOSING ||
			mode == MODE_WIN_SPLIT_Y ||
			mode == MODE_WIN_SPLIT_X)
		return;

	my = wm_win_h - my;

	if (mode == MODE_EDGE_SELECTED) {
		switch (windows[edge].type) {
			case WINDOW_TYPE_SPLIT_X:
				windows[edge].ratio = (mx-edge_x) / (float)edge_w;
				if (windows[edge].ratio < 0.01f)
					windows[edge].ratio = 0.01f;
				else if (windows[edge].ratio > 0.99f)
					windows[edge].ratio = 0.99f;
				wm_require_refresh();
				break;
			case WINDOW_TYPE_SPLIT_Y:
				windows[edge].ratio = (my-edge_y) / (float)edge_h;
				if (windows[edge].ratio < 0.01f)
					windows[edge].ratio = 0.01f;
				else if (windows[edge].ratio > 0.99f)
					windows[edge].ratio = 0.99f;
				wm_require_refresh();
				break;
		}
		active_win = 0;
		return;
	}

	if (wm_capdata()) {
		if (cap.drag) cap.drag(mx, my, wm_win_w, wm_win_h);
		return;
	}

	if (active_win)
		editors[windows[active_win].type].drag(mx-win_x, my-win_y-25,
				win_w, win_h-25);
}

static void keypress(unsigned char key, int x, int y)
{
	if (key == '\e') exit(0);

	if (active_win)
		editors[windows[active_win].type].keypress(key,
				win_w, win_h-25);
}

////////////////////////////////////////
//
// window management
//

static int alloc_win()
{
	int win = windows[0].child[0];
	windows[  0].child[0] = windows[win].child[0];
	windows[win].child[0] = 0;
	return win;
}

static void free_win(int win)
{
	windows[win].type     = WINDOW_TYPE_UNUSED;
	windows[win].child[0] = windows[0].child[0];
	windows[  0].child[0] = win;
}

// close the active win
static void close_win()
{
	int t = (active_win == windows[edge].child[0]);

	free_win(active_win);
	active_win = windows[edge].child[t];
	windows[edge] = windows[active_win];
	free_win(active_win);
}

static void split_win(int type, float ratio)
{
	if (ratio < 0.01f) ratio = 0.01f;
	else if (ratio > 0.99f) ratio = 0.99f;

	int win[2] = {alloc_win(), alloc_win()};
	windows[win[0]].type = windows[win[1]].type = windows[active_win].type;
	windows[win[0]].menu_param.active =
			windows[win[1]].menu_param.active = -1;
	windows[active_win].type  = type;
	windows[active_win].ratio = ratio;
	windows[active_win].child[0] = win[0];
	windows[active_win].child[1] = win[1];

	active_win = 0;
	edge = 0;
}

////////////////////////////////////////
//
// window renderer
//

static void render(int win, int x, int y, int w, int h)
{
	if (d_playing) {
		wm_require_refresh();
		d_refresh(wm_ticks());
	}
	int t;
	switch (windows[win].type) {
		case WINDOW_TYPE_UNUSED: break;
		case WINDOW_TYPE_SPLIT_X:
			t = w * windows[win].ratio;
			render(windows[win].child[0], x, y, t-1, h);
			render(windows[win].child[1], x+t+1, y, w-t-1, h);
			if (mode == MODE_EDGE_SELECTED && win == edge) {
				view2d(x, y, w, h);
				draw_edge_y(t, h);
			}
			break;
		case WINDOW_TYPE_SPLIT_Y:
			t = h * windows[win].ratio;
			render(windows[win].child[0], x, y, w, t-1);
			render(windows[win].child[1], x, y+t+1, w, h-t-1);
			if (mode == MODE_EDGE_SELECTED && win == edge) {
				view2d(x, y, w, h);
				draw_edge_x(t, w);
			}
			break;
		default:
			if (h<=0 || w<=0) break;
			t = (h<25 ? h : 25);
			view2d(x, y, w, t);
			// TODO: draw header
			draw_box_down(0, 0, w, 25, 0.2, 0.2, 0.2);
			// wm_menu[3] is the editor selector
			wm_menu[3].data = &windows[win].type;
			// wm_menu[4] is the sub menu of the editor
			wm_menu[4].data = editors[windows[win].type].menu;
			ui_menu_draw(wm_menu, &windows[win].menu_param, 0, 0);
			view2d(x, y+t, w, h-t);
			editors[windows[win].type].render(w, h-t);
			if (win == active_win) {
				view2d(x, y, w, h);
				draw_outline(0, 0, w, h);
				// splitting
				if (mode == MODE_WIN_SPLIT_Y)
					draw_edge_x(edge_y, w);
				else if (mode == MODE_WIN_SPLIT_X)
					draw_edge_y(edge_x, h);
			}
			break;
	}

	// window closing animation
	if (mode == MODE_WIN_CLOSING) {
		windows[edge].ratio = ferp_out(wm_ticks()-win_close_ticks,
				0, 300, win_close_ratio,
				(active_win == windows[edge].child[1]));
		if (wm_ticks()-win_close_ticks > 300) {
			mode = 0;
			close_win();
		}
		wm_require_refresh();
	}
}

////////////////////////////////////////
//
// view switchers
//

static void view2d(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

////////////////////////////////////////
//
// Callbacks
//

static void close_cb()
{
	if (windows[1].type != WINDOW_TYPE_SPLIT_X &&
			windows[1].type != WINDOW_TYPE_SPLIT_Y)
		return;

	mode = MODE_WIN_CLOSING;
	win_close_ticks = wm_ticks();
	win_close_ratio = windows[edge].ratio;
	wm_require_refresh();
}

static void split_y_cb()
{
	mode = MODE_WIN_SPLIT_Y;
}

static void split_x_cb()
{
	mode = MODE_WIN_SPLIT_X;
}

////////////////////////////////////////
//
// Threads
//

static void * thread_init(void * __unused__)
{
	// more initialization codes here
	// you can set <init_percent> to the desired init progress
	// once it gets to 100, the init is done.

	init_percent = 100;
	return NULL;
}

