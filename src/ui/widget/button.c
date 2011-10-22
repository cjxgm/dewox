
#include "../ui.h"

static void _delete(UI * ui);
static void _paint (UI * ui);

void ui_button_init(UI_BUTTON * btn, int x, int y, int w, int h,
					const char * text)
{
	ui_init(&btn->ui, x, y, w, h);

	UI * ui = (UI *)btn;
	ui->type   = UI_TYPE_BUTTON;
	ui->delete = &_delete;
	ui->paint  = &_paint;

	btn->label = NEW(UI_LABEL);
	ui_label_init(btn->label, 2, 2, w-4, h-4, text);
	btn->label->r = 1.0f;
	btn->label->g = 1.0f;
	btn->label->b = 1.0f;
}

void _delete(UI * ui)
{
	UI_BUTTON * btn = (UI_BUTTON *)ui;
	btn->label->ui.delete(&btn->label->ui);
	free(ui);
}

void _paint(UI * ui)
{
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(ui->x + ui->w, ui->y + ui->h);
	glVertex2f(ui->x, ui->y + ui->h);
	glColor3f(0.25, 0.25, 0.25);
	glVertex2f(ui->x, ui->y);
	glVertex2f(ui->x + ui->w, ui->y);
	glEnd();

	UI_BUTTON * btn = (UI_BUTTON *)ui;
	UI * u = &btn->label->ui;
	u->x += ui->x;
	u->y += ui->y;
	u->paint(u);
	u->x -= ui->x;
	u->y -= ui->y;
}

