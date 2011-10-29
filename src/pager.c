
#include "pager.h"
#include "widget.h"

// in video.c
extern int win_w;
extern int win_h;

page pages[PAGE_SIZE];
int  cpage = 0;

void pager_click(int button, int state, int x, int y)
{
}

void pager_hover(int x, int y)
{
}

void pager_draw()
{
	draw_button(pages[cpage].name, 0, win_h-30, 100, win_h);
}


