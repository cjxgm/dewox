
#include <math.h>
#include "window.h"
#include "common.h"
#include "config.h"
#include "event.h"




static char disabled = 0;
static int  win_w = 800;
static int  win_h = 600;

static void click(int button, int state, int x, int y);
static void drag (int x, int y);
static void hover(int x, int y);
static void key  (unsigned char k, int x, int y);
static void resize(int w, int h);
static void update(int unused);
static void display();




void window_init()
{
	LOG_INFO("[window] glut init\n");
	int argc = 0;
	glutInit(&argc, NULL);

	LOG_INFO("[window] create window\n");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(win_w, win_h);
	glutCreateWindow(VERSION_STRING);

	LOG_INFO("[window] bind events\n");
	glutMouseFunc(&click);
	glutMotionFunc(&drag);
	glutPassiveMotionFunc(&hover);

	glutKeyboardFunc(&key);
	//glutKeyboardUpFunc(&keyup);

	// for taking up less CPU, use TimerFunc not IdleFunc.
	glutTimerFunc(30, &update, 0);
	glutReshapeFunc(&resize);
	glutDisplayFunc(&display);
#ifdef FULLSCREEN
	LOG_INFO("[window] enable fullscreen\n");
	glutFullScreen();
#endif
	
	LOG_INFO("[window] set up bg color\n");
	glClearColor(COLOR_MAIN_BG, 1.0f);

	LOG_INFO("[window] set up anti-aliasing\n");
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void window_run()
{
	LOG_INFO("[window] run\n");
	glutMainLoop();
}




void click(int button, int state, int x, int y)
{
	if (disabled) return;
	event_click(button, state, x, y);
	glutPostRedisplay();
}

void drag(int x, int y)
{
	if (disabled) return;
	event_drag(x, y);
	glutPostRedisplay();
}

void hover(int x, int y)
{
	if (disabled) return;
	event_hover(x, y);
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	if (disabled) return;
	event_key(k);
	glutPostRedisplay();
}

void update(int unused)
{
	glutTimerFunc(30, &update, 0);
	glutPostRedisplay();
}

void resize(int w, int h)
{
	win_w = w;
	win_h = h;

	if (w < 640 || h < 480)
		disabled = 1;
	else
		disabled = 0;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//            v--v----------  make it up-down opposite.
	glOrtho(0, w, h, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void display()
{
	if (disabled) {
		int n = win_w*win_h/2000 + 1;
		glBegin(GL_LINE_LOOP);
		while (n--) {
			float t = rand() & 1;
			t = t/3.0f + 0.6666f;
			glColor3f(t, t, t);
			glVertex2f(rand() % win_w, rand() % win_h);
		}
		glEnd();
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		event_draw(win_w, win_h);
	}
	glutSwapBuffers();
}

