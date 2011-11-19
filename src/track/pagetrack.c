
#include "pagetrack.h"
#include "../widget.h"
#include "../common.h"
#include "../pager.h"
#include "../font.h"
#include "GL/gl.h"

// in video.c
extern int win_w;
extern int win_h;

static int area_h = 100;

static WSplit splits[] = {
	{WSPLIT_HOR , 0, 0, 200},
	{WSPLIT_VERT, 0, 0, 140},
	{WSPLIT_VERT, 0, 0, 140},
};

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
	area_h = win_h - 32;
	/*
	glColor3f(0, 1, 0);
	draw_string_centered(win_w/2, win_h/2, win_w,
		"// TODO: This is the track page.", 0);
	*/
	splits[0].high = win_w;
	splits[1].high = splits[0].value-10;
	splits[2].low  = splits[0].value+10;
	splits[2].high = area_h;

	int i;
	for (i=0; i<LEN(splits); i++)
		draw_split(&splits[i]);
}

