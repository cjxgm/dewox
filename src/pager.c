
#include "config.h"
#include "video.h"
#include "pager.h"
#include "widget.h"
#include "font.h"

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
			i*102, win_h-28, 100, 28);
	}
}

void pager_draw()
{
	int i;
	for (i=0; i<PAGE_SIZE; i++) {
		draw_page_button(pages[i].name, i*102, win_h-28, 100, 28,
			(cpage == i? WSTYLE_SELECTED :
				(pages[i].hovered ? WSTYLE_HOVERED : WSTYLE_NORMAL)));
	}

	glColor3f(1, 1, 1);
	int t = win_w - PAGE_SIZE*102;
	draw_string_centered(PAGE_SIZE*102+t/2, win_h-28+8, t, STATUS_TEXT, 0);

	glBegin(GL_LINES);
	glVertex2f(0, win_h-30);
	glVertex2f(win_w, win_h-30);
	glEnd();
}


