
#include "event.h"
#include "common.h"
#include "widget/widgets.h"




// hooking
void * hooked = NULL;
static ClickFunc hook_click = NULL;
static DragFunc  hook_drag  = NULL;
static HoverFunc hook_hover = NULL;
static KeyFunc   hook_key   = NULL;

static WRadioEntry tabs[] = {
	"Hello,", "World!", "test==", 0
};
//					 		  default	x  y  w		h
static WRadio tab_switcher = {0,		100, 200, 200, 20};




void hook(void * widget, ClickFunc click,
			DragFunc drag, HoverFunc hover, KeyFunc key)
{
	hook_click = click;
	hook_drag  = drag;
	hook_hover = hover;
	hook_key   = key;
	hooked     = widget;
}

void unhook()
{
	hooked = NULL;
	// hook_* = NULL;
}




void event_init()
{
	wradio_new(&tab_switcher, tabs);
}




void event_click(int button, int state, int x, int y)
{
	if (hooked) {
		if (hook_click) hook_click(hooked, button, state, x, y);
		return;
	}

	wradio_click(&tab_switcher, button, state, x, y);
}

void event_drag(int x, int y)
{
	if (hooked) {
		if (hook_drag) hook_drag(hooked, x, y);
		return;
	}
}

void event_hover(int x, int y)
{
	if (hooked) {
		if (hook_hover) hook_hover(hooked, x, y);
		return;
	}

	wradio_hover(&tab_switcher, x, y);
}

void event_key(unsigned char k)
{
	if (hooked) {
		if (hook_key) hook_key(hooked, k);
		return;
	}
}

void event_draw(int w, int h)
{
	wradio_draw(&tab_switcher);
}

