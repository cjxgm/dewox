
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
#include "ui/ui.h"
#include <GL/glut.h>
#include <stdio.h>

int wm_win_w = 640;
int wm_win_h = 480;

#define MODE_EDGE_SELECTED		1
#define MODE_WIN_CLOSING		2
#define MODE_WIN_SPLIT_Y		3
static int mode = 0;
static int edge = 0;
static int edge_x = 0;
static int edge_y = 0;
static int edge_w = 0;
static int edge_h = 0;
static int win_x = 0;
static int win_y = 0;
static int win_w = 0;
static int win_h = 0;

static int active_win = 0;

static void close_cb();
static void split_y_cb();
static void split_x_cb();
static UIMenu wm_menu[] = {
	{UI_MENU_FUNC, &close_cb,   "X"},
	{UI_MENU_FUNC, &split_y_cb, "-"},
	{UI_MENU_FUNC, &split_x_cb, "|"},
	{UI_MENU_EDITOR_SELECTOR},
	{UI_MENU_DONE}
};

// events
static void idle();
static void resize(int w, int h);
static void hover(int mx, int my);
static void click(int btn, int stt, int mx, int my);
static void drag(int mx, int my);

// window management
#define WINDOW_TYPE_UNUSED		0
#define WINDOW_TYPE_SPLIT_X		1
#define WINDOW_TYPE_SPLIT_Y		2
#define WINDOW_TYPE_TEST		3
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

static struct WindowEntry
{
	const char * name;
	WindowRenderFunc * render;
} window_entries[WM_MAX_WINDOW_ENTRY_CNT];

static int alloc_win();
static void free_win(int win);
static void close_win();
static void split_win(int type, float ratio);

// some useful functions
static void render(int win, int x, int y, int w, int h);
static void view2d(int x, int y, int w, int h);
static void draw_edge_y(int x, int h);
static void draw_edge_x(int y, int w);
static void draw_box_down(int x, int y, int w, int h,
		float r, float g, float b);
static void draw_outline(int x, int y, int w, int h);

// window: test
static void test_render(int w, int h);

////////////////////////////////////////
//
// externals
//

inline void wm_init()
{
	// init glut
	int argc = 0;
	glutInit(&argc, NULL);

	// create render window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(wm_win_w, wm_win_h);
	glutCreateWindow("Dewox");

	// bind events
	glutDisplayFunc(&wm_require_refresh);
	glutReshapeFunc(&resize);
	glutPassiveMotionFunc(&hover);
	glutMotionFunc(&drag);
	glutMouseFunc(&click);

	// setup blank color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// setup anti-aliasing for points and lines
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// init windows
	int i;
	for (i=0; i<WM_MAX_WINDOW_CNT; i++) {
		//windows[i].type   = WINDOW_TYPE_UNUSED;
		//windows[i].edge_flag = EDGE_FLAG_NONE;
		windows[i].child[0] = i + 1;
		windows[i].menu_param.active = -1;
	}
	windows[WM_MAX_WINDOW_CNT-1].child[0] = 0;

	// register internal windows
	wm_register_window("unused", NULL);
	wm_register_window("split-x", NULL);
	wm_register_window("split-y", NULL);

	// test
	wm_register_window("test", test_render);

	int win = alloc_win();
	windows[win].type = WINDOW_TYPE_SPLIT_X;
	windows[win].child[0] = alloc_win();
	windows[win].child[1] = alloc_win();
	windows[win].ratio    = 0.7f;
	windows[windows[win].child[0]].type = WINDOW_TYPE_TEST;

	win = windows[win].child[1];
	windows[win].type = WINDOW_TYPE_SPLIT_Y;
	windows[win].child[0] = alloc_win();
	windows[win].child[1] = alloc_win();
	windows[win].ratio    = 0.7f;
	windows[windows[win].child[0]].type = WINDOW_TYPE_TEST;
	windows[windows[win].child[1]].type = WINDOW_TYPE_TEST;
}

inline void wm_mainloop()
{
	glutMainLoop();
}

inline void wm_require_refresh()
{
	glutIdleFunc(&idle);
}

void wm_register_window(const char * name, WindowRenderFunc * render)
{
	int i = 0;
	while (window_entries[i].name) i++;
	window_entries[i].name   = name;
	window_entries[i].render = render;
}

////////////////////////////////////////
//
// events
//

static void idle()
{
	glutIdleFunc(NULL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render(1, 0, 0, wm_win_w, wm_win_h);
	glutSwapBuffers();
}

static void resize(int w, int h)
{
	wm_win_w = w;
	wm_win_h = h;
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

	// TODO: mouse event for header
	if (my-win_y < 25) {
		ui_menu_hover(wm_menu, &windows[active_win].menu_param,
				0, 0, mx-win_x, my-win_y);
		return;
	}

	// TODO: mouse event for window
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
	}
	if (active_win && btn == GLUT_LEFT_BUTTON && stt == GLUT_DOWN)
		ui_menu_click(wm_menu, &windows[active_win].menu_param,
				0, 0, mx, my);
}

static void drag(int mx, int my)
{
	if (mode == MODE_WIN_CLOSING) return;

	my = wm_win_h - my;

	if (mode == MODE_EDGE_SELECTED) {
		switch (windows[edge].type) {
			case WINDOW_TYPE_SPLIT_X:
				windows[edge].ratio = (mx-edge_x) / (float)edge_w;
				if (windows[edge].ratio < 0)
					windows[edge].ratio = 0;
				else if (windows[edge].ratio > 1)
					windows[edge].ratio = 1;
				wm_require_refresh();
				break;
			case WINDOW_TYPE_SPLIT_Y:
				windows[edge].ratio = (my-edge_y) / (float)edge_h;
				if (windows[edge].ratio < 0)
					windows[edge].ratio = 0;
				else if (windows[edge].ratio > 1)
					windows[edge].ratio = 1;
				wm_require_refresh();
				break;
		}
	}
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
	if (windows[1].type != WINDOW_TYPE_SPLIT_X &&
			windows[1].type != WINDOW_TYPE_SPLIT_Y)
		return;

	int t = (active_win == windows[edge].child[0]);

	free_win(active_win);
	active_win = windows[edge].child[t];
	windows[edge] = windows[active_win];
	free_win(active_win);
}

static void split_win(int type, float ratio)
{
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
			t = (h<25 ? h : 25);
			view2d(x, y, w, t);
			// TODO: draw header
			draw_box_down(0, 0, w, 25, 0.2, 0.2, 0.2);
			ui_menu_draw(wm_menu, &windows[win].menu_param, 0, 0);
			view2d(x, y+t, w, h-t);
			window_entries[windows[win].type].render(w, h);
			if (win == active_win) {
				view2d(x, y, w, h);
				draw_outline(0, 0, w, h);
				// splitting
				if (mode == MODE_WIN_SPLIT_Y) {
					view2d(x, y, w, h);
					draw_edge_x(edge_y, w);
				}
			}
			break;
	}

	// window closing animation
	if (mode == MODE_WIN_CLOSING) {
		if (active_win == windows[edge].child[0]) {
			if ((windows[edge].ratio -= 0.01) < 0) {
				mode = 0;
				close_win();
			}
		}
		else {
			if ((windows[edge].ratio += 0.01) > 1) {
				mode = 0;
				close_win();
			}
		}
		wm_require_refresh();
	}
}

static void draw_edge_y(int x, int h)
{
	glLineWidth(4);
	glColor3f(0.2f, 0.2f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(x, 0);
	glVertex2f(x, h);
	glEnd();
}

static void draw_edge_x(int y, int w)
{
	glLineWidth(4);
	glColor3f(0.2f, 0.2f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, y);
	glVertex2f(w, y);
	glEnd();
}

static void draw_box_down(int x, int y, int w, int h,
		float r, float g, float b)
{
	glBegin(GL_QUADS);
	glColor3f(r * 1.1f, g * 1.1f, b * 1.1f);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glColor3f(r * 0.9f, g * 0.9f, b * 0.9f);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glEnd();
}

static void draw_outline(int x, int y, int w, int h)
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor4f(0.2f, 0.2f, 1.0f, 0.3f);
	glVertex2f(x-1, y-1);
	glVertex2f(x+w+1, y-1);
	glVertex2f(x+w+1, y+h+1);
	glVertex2f(x-1, y+h+1);
	glColor4f(0.2f, 0.2f, 1.0f, 0.7f);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	glColor4f(0.2f, 0.2f, 1.0f, 1.0f);
	glVertex2f(x+1, y+1);
	glVertex2f(x+w-1, y+1);
	glVertex2f(x+w-1, y+h-1);
	glVertex2f(x+1, y+h-1);
	glEnd();
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
	mode = MODE_WIN_CLOSING;
	wm_require_refresh();
}

static void split_y_cb()
{
	mode = MODE_WIN_SPLIT_Y;
}

static void split_x_cb()
{
}

////////////////////////////////////////
//
// test
//

static void test_render(int w, int h)
{
	glBegin(GL_POINTS);
	int x,y;
	for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			glColor3f(x/(float)w, y/(float)h,
						x*y/(float)w/(float)h);
			glVertex2f(x, y);
		}
	glEnd();
}

