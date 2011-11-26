
#ifndef __WIDGET__
#define __WIDGET__


typedef enum WState
{
	WSTATE_NORMAL,
	WSTATE_HOVERED,
	WSTATE_PRESSED,
	WSTATE_SELECTED,
}
WState;


int hovertest_box(int mx, int my, int x, int y, int w, int h);


#endif

