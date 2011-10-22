
#include "../UI.h"

void Button::paint()
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

	label->x += x;
	label->y += y;
	label->paint();
	label->x -= x;
	label->y -= y;
}

void Button::resize(int w, int h)
{
	UI::resize(w, h);

	label->resize(10 * label->text.length(), 16);
	label->move((w - label->w) >> 1, (h - label->h) >> 1);
	label->hidden = (label->x < 10);
}

