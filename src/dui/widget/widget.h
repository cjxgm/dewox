
#ifndef __WIDGET__
#define __WIDGET__


typedef enum WState
{
	WSTATE_NORMAL,
	WSTATE_HOVERED,
	WSTATE_PRESSED,
	WSTATE_EDITING,
}
WState;


float hovertest_box(float mx, float my,
		float x, float y, float w, float h);
void draw_border(float x, float y, float w, float h);

void draw_msgbox(float x, float y, float w,
		const char * title, const char * label, WState state);

#endif

