
#include "video.h"
#include "widget.h"

// pager and pages
#include "pager.h"
#include "pagefile.h"

// in video.c
extern int win_w;
extern int win_h;

int main()
{
	// font_init();
	pagefile_init();

	video_init();
	video_run();
	return 0;
}

void main_click(int button, int state, int x, int y)
{
	if (hovertest_box(x, y, 0, win_h-30, win_w, win_h))
		pager_click(button, state, x, y);
	else if (pages[cpage].click)
		pages[cpage].click(button, state, x, y);
}

void main_drag(int x, int y)
{
	if (hovertest_box(x, y, 0, win_h-30, win_w, win_h))
		return;
	else if (pages[cpage].click)
		pages[cpage].drag(x, y);
}

void main_hover(int x, int y)
{
	if (hovertest_box(x, y, 0, win_h-30, win_w, win_h))
		pager_hover(x, y);
	else if (pages[cpage].click)
		pages[cpage].hover(x, y);
}

void main_key(unsigned char k, int x, int y)
{
	if (hovertest_box(x, y, 0, win_h-30, win_w, win_h))
		return;
	else if (pages[cpage].click)
		pages[cpage].key(k, x, y);
}

void main_render()
{
	if (pages[cpage].click)
		pages[cpage].draw();
	pager_draw();
}

