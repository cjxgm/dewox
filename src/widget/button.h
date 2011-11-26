
#ifndef __WIDGET_BUTTON__
#define __WIDGET_BUTTON__

#include "widget.h"

typedef struct WButton
{
	const char * label;
	int x, y, w, h;
	WState state;
}
WButton;

void wbutton_draw (WButton * w);
void wbutton_click(WButton * w, int button, int state, int x, int y);
void wbutton_hover(WButton * w, int x, int y);

#endif

