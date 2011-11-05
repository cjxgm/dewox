
#include "video.h"
#include "pager.h"
#include "widget.h"

// in video.c
extern int win_w;
extern int win_h;

page pages[PAGE_SIZE];
int  cpage = 0;

void pager_click(int button, int state, int x, int y)
{
	if (button == MOUSE_LEFT && state == MOUSE_DOWN) {
		int i;
		for (i=0; i<PAGE_SIZE; i++) {
			if (pages[i].hovered) {
				cpage = i;
				break;
			}
		}
	}
}

void pager_hover(int x, int y)
{
	int i;
	for (i=0; i<PAGE_SIZE; i++) {
		pages[i].hovered = hovertest_box(x, y,
			i*102, win_h-30, 100, 30);
	}
}

void pager_draw()
{
	int i;
	for (i=0; i<PAGE_SIZE; i++) {
		draw_button(pages[i].name, i*102, win_h-30, 100, 30,
			(cpage == i? 2 : pages[i].hovered));
	}
}


