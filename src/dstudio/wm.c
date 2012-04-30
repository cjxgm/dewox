
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
#include <GL/glut.h>

int wm_win_w = 640;
int wm_win_h = 480;

static void idle();
static void resize(int w, int h);


#define WINDOW_TYPE_UNUSED		0
#define WINDOW_TYPE_SPLIT_X		1
#define WINDOW_TYPE_SPLIT_Y		2
#define WINDOW_TYPE_TEST		3
static struct WindowInfo
{
	int type;
	int child[2];
	float ratio;
} windows[WM_MAX_WINDOW_CNT];

static struct WindowEntry
{
	const char * name;
	WindowRenderFunc * render;
} window_entries[WM_MAX_WINDOW_ENTRY_CNT];

static int alloc_win();
static void free_win(int win);


static void render(int win, int x, int y, int w, int h);
static void view2d(int x, int y, int w, int h);

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
		windows[i].child[0] = i + 1;
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

void wm_register_window(const char * name, WindowRenderFunc * render)
{
	int i = 0;
	while (window_entries[i].name) i++;
	window_entries[i].name   = name;
	window_entries[i].render = render;
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
			render(windows[win].child[0], x, y, t-2, h);
			render(windows[win].child[1], x+t, y, w-t, h);
			break;
		case WINDOW_TYPE_SPLIT_Y:
			t = h * windows[win].ratio;
			render(windows[win].child[0], x, y, w, t-2);
			render(windows[win].child[1], x, y+t, w, h-t);
			break;
		default:
			view2d(x, y, w, h);
			window_entries[windows[win].type].render(w, h);
			break;
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

