
#include "../UI.h"

void Button::paint()
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

void Button::mouseEvent(MouseEventType t, MouseButtonType b, int x, int y)
{
	if (pressed) {
		if (t == MOUSE_MOVE)
			onDrag(x, y);
		if (b == MOUSE_LEFT && t == MOUSE_UP) {
			eventManager.mouseHooker = NULL;
			pressed = false;
			onPressed(x, y);
		}
		return;
	}

	if (hidden) return;

	if (x < this->x
		|| y < this->y
		|| x > this->x + w
		|| y > this->y + h)
		return;

	if (b == MOUSE_LEFT && t == MOUSE_DOWN) {
		eventManager.mouseHooker = this;
		pressed = true;
	}
}
