
#include "../ui.h"
#include "font.h"

static void _delete(UI * ui);
static void _paint (UI * ui);

static void draw_char(unsigned char ch, int x, int y);

void ui_label_init(UI_LABEL * lb, int x, int y, int w, int h,
					const char * text)
{
	ui_init(&lb->ui, x, y, w, h);
	UI * ui = (UI *)lb;
	ui->type   = UI_TYPE_LABEL;
	ui->delete = &_delete;
	ui->paint  = &_paint;
	lb->text   = text;
}

static void _delete(UI * ui)
{
	free(ui);
}

void _paint(UI * ui)
{
	if (ui->hidden) return;
	if (ui->h < 16 || ui->w < 10) return;

	const char * s = ((UI_LABEL *)ui)->text;
	float * color  = &((UI_LABEL *)ui)->r;
	int x = 0;

	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	while (*s) {
		if (x + 10 > ui->w) break;
		draw_char(*s++, ui->x + x, ui->y);
		x += 10;
	}
	glEnd();
}

void draw_char(unsigned char ch, int x, int y)
{
	int a, b;
	for (b=0; b<16; b++) {
		char t = font[ch*16+b];
		for (a=0; a<8; a++)
			if ((t >> (7 - a)) & 1)
			glVertex2f(x+a, 16+y-b);
	}
}

