
#ifndef __WIDGET_RANGE__
#define __WIDGET_RANGE__

#include "widget.h"




typedef struct WRange
{
	float x, y, w, h;
	float min, max, step, value;

	int   tmpx;
	float tmpf;

	WState state;
}
WRange;




void wrange_draw (WRange * w);
void wrange_click(WRange * w, int button, int state, int x, int y);
void wrange_drag (WRange * w, int x, int y);
void wrange_hover(WRange * w, int x, int y);
void wrange_key  (WRange * w, unsigned char k);

#endif

