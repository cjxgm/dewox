
#include "video.h"

int win_w;
int win_h;

// in main.c
extern void main_click(int button, int state, int x, int y);
extern void main_drag(int x, int y);
extern void main_hover(int x, int y);
extern void main_key(unsigned char k, int x, int y);
extern void main_render();

static void click(int button, int state, int x, int y);
static void drag(int x, int y);
static void hover(int x, int y);
static void key(unsigned char k, int x, int y);
static void resize(int w, int h);
static void update(int unused);
static void display();

// Initialize OpenGL
void video_init()
{
	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("dewox");

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
	glutFullScreen();
#endif
	
	glClearColor(0, 0, 0, 0);
}

void video_run()
{
	glutMainLoop();
}

void click(int button, int state, int x, int y)
{
	main_click(button, state, x, y);
	glutPostRedisplay();
}

void drag(int x, int y)
{
	main_drag(x, y);
	glutPostRedisplay();
}

void hover(int x, int y)
{
	main_hover(x, y);
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	main_key(k, x, y);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	main_render();
	glutSwapBuffers();
}

