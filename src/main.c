
#include <GL/gl.h>

#include "video.h"
#include "widget.h"
#include "font.h"

// pager and pages
#include "pager.h"
#include "pagefile.h"
#include "scene/pagescene.h"

// in video.c
extern int win_w;
extern int win_h;

int disabled = 0;// When the screen is too small everything will be diabled.

int main()
{
	// font_init();
	pagefile_init();
	pagescene_init();

	video_init();
	video_run();
	return 0;
}

void main_click(int button, int state, int x, int y)
{
	if (disabled) return;
	pager_click(button, state, x, y);
	if (pages[cpage].click)
		pages[cpage].click(button, state, x, y);
}

void main_drag(int x, int y)
{
	if (disabled) return;
	if (pages[cpage].drag)
		pages[cpage].drag(x, y);
}

void main_hover(int x, int y)
{
	if (disabled) return;
	pager_hover(x, y);
	if (pages[cpage].hover)
		pages[cpage].hover(x, y);
}

void main_key(unsigned char k, int x, int y)
{
	if (disabled) return;
	if (pages[cpage].key)
		pages[cpage].key(k, x, y);
}

void main_render()
{
	disabled = (win_w < 640 || win_h < 480);

	if (disabled) {
		glColor3f(1, 0, 0);
		draw_string_centered(win_w/2, win_h/2, win_w, "Please make the window larger than 640x480!", 0);
		return;
	}

	if (pages[cpage].draw)
		pages[cpage].draw();
	pager_draw();
}

