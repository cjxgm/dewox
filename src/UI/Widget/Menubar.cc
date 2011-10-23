
#include "../UI.h"

void Menubar::paint()
{
	if (hidden) return;

	glBegin(GL_QUADS);
	colorManager.bgMenubar1->apply();
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	colorManager.bgMenubar2->apply();
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glEnd();

	UI * ui;
	widgets->iterBegin();
	while (!widgets->iterDone()) {
		ui = widgets->iterGet();
		if (ui->x < 0 || ui->y < 0
			|| ui->x+ui->w > w || ui->y+ui->h > h)
			continue;
		ui->move(ui->x + x, ui->y + y);
		ui->paint();
		ui->move(ui->x - x, ui->y - y);
	}
}

void Menubar::resize(int w, int h)
{
	UI::resize(w, h);

	if (menubarType == MENUBAR_H)
		h = 20;
	else {/*TODO*/}
}

