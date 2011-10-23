
#include "../UI.h"
#include "../../Dewox/App.h"

extern App * app;

void HSplit::paint()
{
	if (hidden) return;

	glBegin(GL_QUADS);
	if (pressed) colorManager.bgButton2->apply();
	else		 colorManager.bgButton1->apply();
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	if (pressed) colorManager.bgButton1->apply();
	else		 colorManager.bgButton2->apply();
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glEnd();
}

void HSplit::onDrag(int x, int y)
{
	app->update();
	move(this->x, y - h / 2);
}

void HSplit::onPressed(int x, int y)
{
	app->update();
	move(this->x, y - h / 2);
}
