
#include <GL/gl.h>

#include "pageconfig.h"
#include "pager.h"
#include "font.h"

// in video.c
extern int win_w;
extern int win_h;

static void pageconfig_draw();

void pageconfig_init()
{
	pages[PAGE_CONFIG] = (page){
		"Config",
		.draw = &pageconfig_draw
	};
}

void pageconfig_draw()
{
	glColor3f(0, 1, 0);
	draw_string_centered(win_w/2, win_h/2, win_w,
		"// TODO: This is the config page.", 0);
}

