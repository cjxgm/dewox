
#include "pagefile.h"
#include "pager.h"
#include "font.h"
#include "GL/gl.h"

// in video.c
extern int win_w;
extern int win_h;

static void pagefile_draw();

void pagefile_init()
{
	pages[PAGE_FILE] = (page){
		"file",
		.draw = &pagefile_draw
	};
}

void pagefile_draw()
{
	glColor3f(0, 1, 0);
	draw_string_centered(win_w/2, win_h/2, win_w,
		"// TODO: This is the file page.", 0);
}

