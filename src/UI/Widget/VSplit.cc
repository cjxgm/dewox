
#include "../UI.h"
#include "../../Dewox/App.h"

extern App * app;

void VSplit::paint()
{
	if (hidden) return;

	glBegin(GL_QUADS);
	if (pressed) colorManager.bgButton2->apply();
	else		 colorManager.bgButton1->apply();
	glVertex2f(x, y + h);
	glVertex2f(x, y);
	if (pressed) colorManager.bgButton1->apply();
	else		 colorManager.bgButton2->apply();
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glEnd();
}

void VSplit::onDrag(int x, int y)
{
	app->update();
	move(x - w / 2, this->y);
}

void VSplit::onPressed(int x, int y)
{
	app->update();
	move(x - w / 2, this->y);
}
