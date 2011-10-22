
#include "ui.h"

static void _delete(UI * ui);

void ui_init(UI * ui, int x, int y, int w, int h)
{
	ui->type   = UI_TYPE_UNKNOWN;
	ui->delete = &_delete;
	ui->paint  = NULL;

	ui->x = x;
	ui->y = y;
	ui->w = w;
	ui->h = h;
}

void _delete(UI * ui)
{
	assert(ui->type == UI_TYPE_UNKNOWN);
	free(ui);
}

/* It may be useful some other places.
void _paint(UI * ui)
{
	// no need to draw this.
	if (!ui->render) return;

	glPushAttrib(GL_VIEWPORT_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glViewport(ui->x, ui->y, ui->w, ui->h);
	glOrtho(0, ui->w+1, 0, ui->h+1, 0, 100);
	glMatrixMode(GL_MODELVIEW);

	ui->render(ui);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);
}
*/

