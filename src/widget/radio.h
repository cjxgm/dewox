
#ifndef __WIDGET_RADIO__
#define __WIDGET_RADIO__

#include "widget.h"
#include "button.h"




typedef const char * WRadioEntry;

typedef struct WRadio
{
	int selected;
	int x, y, w, h;
	WState state;

	WButton * btns;
	int btn_cnt;
}
WRadio;




void wradio_new  (WRadio * w, WRadioEntry entries[]);
void wradio_draw (WRadio * w);
void wradio_click(WRadio * w, int button, int state, int x, int y);
void wradio_drag (WRadio * w, int x, int y);
void wradio_hover(WRadio * w, int x, int y);

#endif

