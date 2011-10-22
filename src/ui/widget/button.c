
#include "../ui.h"

static void _delete(UI * ui);
static void _paint (UI * ui);
static void _resize(UI * ui, int w, int h);

void ui_button_init(UI_BUTTON * btn, int x, int y, int w, int h,
					const char * text)
{
	ui_init(&btn->ui, x, y, w, h);

	UI * ui = (UI *)btn;
	ui->type   = UI_TYPE_BUTTON;
	ui->delete = &_delete;
	ui->paint  = &_paint;
	ui->resize = &_resize;

	btn->label = NEW(UI_LABEL);
	ui_label_init(btn->label, 0, 0, 0, 0, text);
	ui->resize(ui, w, h);	// so that label size can be recalculated
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
	if (ui->hidden) return;

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

static void _resize(UI * ui, int w, int h)
{
	ui->w = w;
	ui->h = h;

	UI_LABEL * lb = ((UI_BUTTON *)ui)->label;
	UI * u = &lb->ui;
	u->resize(u, 10 * strlen(lb->text), 16);
	u->move(u, (w - u->w) >> 1, (h - u->h) >> 1);
	u->hidden = (u->x < 10);
}

