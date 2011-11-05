
#include "pagetrack.h"
#include "../pager.h"
#include "../font.h"
#include "GL/gl.h"

// in video.c
extern int win_w;
extern int win_h;

static void pagetrack_draw();

void pagetrack_init()
{
	pages[PAGE_TRACK] = (page){
		"Track",
		.draw = &pagetrack_draw
	};
}

void pagetrack_draw()
{
	glColor3f(0, 1, 0);
	draw_string_centered(win_w/2, win_h/2, win_w,
		"// TODO: This is the track page.", 0);
}

