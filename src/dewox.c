
#include <stdlib.h>

#include "event.h"
#include "common.h"
#include "widget/widgets.h"




static WRadioItem tabs[] = {
	"Hello,", "World!", "test==", "VERY VERY LONG", NULL
};
//					 		  default	x	  y	  w		h	items
static WRadio tab_switcher = {0,		100, 200, 250, 20, tabs};

static WButton btn = {"Quit", 100, 230, 250, 20};




static void act_quit(void * w)
{
	exit(0);
}




void app_click(int button, int state, int x, int y)
{
	wradio_click(&tab_switcher, button, state, x, y);
	wbutton_click(&btn, button, state, x, y);
}

void app_drag(int x, int y)
{
}

void app_hover(int x, int y)
{
	wradio_hover(&tab_switcher, x, y);
	wbutton_hover(&btn, x, y);
}

void app_key(unsigned char k)
{
	if (k == '\e')
		msgbox(&btn, act_quit, "Quit? You pressed ESC for it.", "Sure");
}

void app_draw(int w, int h)
{
	tab_switcher.w = w-200;
	btn.w = w-200;

	wradio_draw(&tab_switcher);
	wbutton_draw(&btn);

	if (btn.clicked) {
		btn.clicked = 0;
		msgbox(&btn, act_quit, "Quit?", "Sure???? So LONG A Message!");
	}
}

