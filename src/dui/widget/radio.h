
#ifndef __WIDGET_RADIO__
#define __WIDGET_RADIO__

#include "widget.h"




typedef const char * WRadioItem;

typedef struct WRadio
{
	int selected;
	float x, y, w, h;
	WRadioItem * items;
	WState state;

	int tmp;
}
WRadio;




void wradio_draw (WRadio * w);
void wradio_click(WRadio * w, int button, int state, int x, int y);
void wradio_hover(WRadio * w, int x, int y);

#endif

