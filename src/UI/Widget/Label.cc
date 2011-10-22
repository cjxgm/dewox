
#include "../UI.h"
#include "Font.h"

static void draw_char(unsigned char ch, int x, int y);

void Label::paint()
{
	if (hidden) return;
	if (h < 16 || w < 10) return;

	glBegin(GL_POINTS);
	color.apply();
	for (int i=0; i<text.length(); i++) {
		if ((i + 1) * 10 > w) break;
		draw_char(text[i], x + i * 10, y);
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

