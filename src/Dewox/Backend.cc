
#include "Backend.h"
#include <GL/glut.h>
#include "../UI/UI.h"

static void resize(int w, int h);
static void render();
static void mouse(int button, int state, int x, int y);
static void motion(int x, int y);
static void key(unsigned char keycode, int x, int y);
static void keyup(unsigned char keycode, int x, int y);

static KeyEventType   * key_states;
static MouseEventType * mouse_states;

void Backend::run()
{
	key_states   = new KeyEventType[256];
	mouse_states = new MouseEventType[3];

	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Dewox UI Experiments");

	glutMouseFunc(&mouse);
	glutMotionFunc(&motion);
	glutPassiveMotionFunc(&motion);

	glutKeyboardFunc(&key);
	glutKeyboardUpFunc(&keyup);

	glutIdleFunc(&render);
	glutReshapeFunc(&resize);

	glutFullScreen();
	glutMainLoop();
}

void resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(0, w + 1, 0, h + 1, 0, 100);
	glMatrixMode(GL_MODELVIEW);

	app->resize(w, h);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	app->paint();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	y = app->h - y;

	switch (button) {
		case GLUT_LEFT_BUTTON:   button = MOUSE_LEFT;   break;
		case GLUT_RIGHT_BUTTON:  button = MOUSE_RIGHT;  break;
		case GLUT_MIDDLE_BUTTON: button = MOUSE_MIDDLE; break;
	}
	switch (state) {
		case GLUT_UP:   state = MOUSE_UP;   break;
		case GLUT_DOWN: state = MOUSE_DOWN; break;
	}

	eventManager.mouseEvent((MouseEventType)state,
							(MouseButtonType)button, x, y);

	if (state == MOUSE_UP && mouse_states[button] == MOUSE_DOWN)
		eventManager.mouseEvent(MOUSE_CLICK,
							(MouseButtonType)button, x, y);

	mouse_states[button] = (MouseEventType)state;
}

void motion(int x, int y)
{
	y = app->h - y;

	eventManager.mouseEvent(MOUSE_MOVE, MOUSE_LEFT, x, y);
}

void key(unsigned char keycode, int x, int y)
{
	int mod  = glutGetModifiers();
	int mod2 = 0;
	if (mod & GLUT_ACTIVE_ALT)   mod2 |= KEY_ALT;
	if (mod & GLUT_ACTIVE_CTRL)  mod2 |= KEY_CTRL;
	if (mod & GLUT_ACTIVE_SHIFT) mod2 |= KEY_SHIFT;

	eventManager.keyEvent(KEY_DOWN, keycode, mod2);

	key_states[keycode] = KEY_DOWN;
}

void keyup(unsigned char keycode, int x, int y)
{
	int mod  = glutGetModifiers();
	int mod2 = 0;
	if (mod & GLUT_ACTIVE_ALT)   mod2 |= KEY_ALT;
	if (mod & GLUT_ACTIVE_CTRL)  mod2 |= KEY_CTRL;
	if (mod & GLUT_ACTIVE_SHIFT) mod2 |= KEY_SHIFT;

	eventManager.keyEvent(KEY_UP, keycode, mod2);

	if (key_states[keycode] == KEY_DOWN)
		eventManager.keyEvent(KEY_PRESSED, keycode, mod2);

	key_states[keycode] = KEY_DOWN;
}

