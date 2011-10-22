
#include "backend.h"
#include <GL/glut.h>
#include "ui.h"

static LIST * widgets;

typedef struct view
{
	int x, y, w, h;
}
VIEW;

VIEW win_view;

void resize(int w, int h)
{
	win_view = (VIEW){0, 0, w, h};
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(0, w + 1, 0, h + 1, 0, 100);
	glMatrixMode(GL_MODELVIEW);
}

void render()
{
	VIEW * v = &win_view;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(v->x + v->w, v->y + v->h);
	glVertex2f(v->x, v->y + v->h);
	glVertex2f(v->x, v->y);
	glVertex2f(v->x + v->w, v->y);
	glEnd();
	glColor3f(0.4, 0, 0);
	glRectf(v->x+1, v->y+1, v->x + v->w, v->y + v->h);

	LIST * lst = widgets;
	while ((lst = lst->next) != widgets)
		ui_get(lst)->paint(ui_get(lst));

	glutSwapBuffers();
}

void backend_run()
{
	int argc = 0;
	glutInit(&argc, NULL);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Maze");
	glutIdleFunc(&render);
	glutReshapeFunc(&resize);

	widgets = list_new();
	LIST * lst;

	lst = NEW(LIST);
	lst->data = NEW(UI_BUTTON);
	ui_button_init(lst->data, 10, 10, 100, 20, "Hello!");
	list_append(widgets, lst);

	glutMainLoop();
}
