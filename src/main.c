

#include <GL/glut.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// in stacking.c
extern void * thread_play(void * a);
extern void click(int btn, int stt, int x, int y);
extern void drag(int x, int y);
extern void hover(int x, int y);
extern void draw();
extern void keypress(int key, int x, int y);

int win_w;
int win_h;

FILE * dsp;
pthread_t play_thread;

static void resize(int w, int h)
{
	win_w = w;
	win_h = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
}

static void display()
{
	// const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
	glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
	keypress(key, x, y);
	glutPostRedisplay();
}

static void timer()
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	dsp = fopen("/dev/dsp", "wb");
	if (!dsp) {
		fprintf(stderr, "Unable to open /dev/dsp!\n");
		return 1;
	}

	extern int playing;
	pthread_create(&play_thread, NULL, &thread_play, &playing);

	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Stacking Experiment");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMouseFunc(click);
	glutMotionFunc(drag);
	glutPassiveMotionFunc(hover);
	glutIdleFunc(&timer);

	glClearColor(0, 0, 0, 0);

	glutMainLoop();

	return EXIT_SUCCESS;
}

