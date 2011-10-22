
#include "Backend.h"
#include <GL/glut.h>
#include "../UI/UI.h"

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

void Backend::run()
{
	int argc = 0;
	glutInit(&argc, NULL);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Dewox UI Experiments");
	glutIdleFunc(&render);
	glutReshapeFunc(&resize);

	glutMainLoop();
}

