
#include "../UI.h"

void VSplit::paint()
{
	if (hidden) return;

	glBegin(GL_QUADS);
	colorManager.bgButton1->apply();
	glVertex2f(x, y + h);
	glVertex2f(x, y);
	colorManager.bgButton2->apply();
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glEnd();
}

