
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
	if (focused)
		colorManager.focusFrameBorder->apply();
	else
		colorManager.unfocusFrameBorder->apply();
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glEnd();
}

void Frame::mouseEvent(MouseEventType t, MouseButtonType b, int x, int y)
{
	switch ((int)t) {
		case MOUSE_MOVE:
			focused = (x > this->x
					&& y > this->y
					&& x < this->x + w
					&& y < this->y + h);
			break;
	}
}

