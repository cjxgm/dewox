
#include "../UI.h"

void HSplit::paint()
{
	if (hidden) return;

	glBegin(GL_QUADS);
	colorManager.bgButton1->apply();
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	colorManager.bgButton2->apply();
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glEnd();
}

