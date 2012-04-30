
/************************************************************
 * dewox: wm.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "wm.h"
#include <GL/glut.h>

int wm_win_w = 640;
int wm_win_h = 480;

static void idle();
static void resize(int w, int h);

static void render();
static void view2d(int x0, int y0, int x1, int y1);

inline void wm_init()
{
	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(wm_win_w, wm_win_h);
	glutCreateWindow("Dewox");

	/*
	glutMouseFunc(&click);
	glutMotionFunc(&drag);
	glutPassiveMotionFunc(&hover);

	glutKeyboardFunc(&key);
	//glutKeyboardUpFunc(&keyup);

	// for taking up less CPU, use TimerFunc not IdleFunc.
	glutTimerFunc(30, &update, 0);
	glutReshapeFunc(&resize);
	glutDisplayFunc(&display);
	*/

	//glutFullScreen();
	glutDisplayFunc(&wm_require_refresh);
	glutReshapeFunc(&resize);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

inline void wm_mainloop()
{
	glutMainLoop();
}

inline void wm_require_refresh()
{
	glutIdleFunc(&idle);
}




static void idle()
{
	glutIdleFunc(NULL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render();
	glutSwapBuffers();
}

static void resize(int w, int h)
{
	wm_win_w = w;
	wm_win_h = h;
}

static void render()
{
	view2d(0, 0, wm_win_w, wm_win_h);
	glBegin(GL_POINTS);
	int x,y;
	for (y=0; y<wm_win_h; y++)
		for (x=0; x<wm_win_w; x++) {
			glColor3f(x/(float)wm_win_w, y/(float)wm_win_h,
						x*y/(float)wm_win_w/(float)wm_win_h);
			glVertex2f(x, y);
		}
	glEnd();
}

static void view2d(int x0, int y0, int x1, int y1)
{
	glViewport(x0, y0, x1, y1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x0, x1, y0, y1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

