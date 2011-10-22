
#include "../UI.h"

void Frame::paint()
{
	if (hidden) return;

	glBegin(GL_QUADS);
	colorManager.bgFrame->apply();
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glEnd();

	glBegin(GL_LINE_LOOP);
	colorManager.unfocusFrameBorder->apply();
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glEnd();
}

