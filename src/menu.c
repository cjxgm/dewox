
#ifndef NULL
#define NULL ((void *)0)
#endif

char is_menu = 0;

static void (*draw)() = NULL;
static void (*click)(int btn, int stt, int x, int y) = NULL;
static void (*hover)(int x, int y) = NULL;

void menu_open(void (*mdraw)(),
							 void (*mclick)(int btn, int stt, int x, int y),
							 void (*mhover)(int x, int y))
{
	draw = mdraw;
	click = mclick;
	hover = mhover;
	is_menu = 1;
}

void menu_draw()
{
	if (draw) draw();
}

void menu_click(int btn, int stt, int x, int y)
{
	if (click) click(btn, stt, x, y);
}

void menu_hover(int x, int y)
{
	if (hover) hover(x, y);
}
