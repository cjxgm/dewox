
#include "event.h"
#include "common.h"
#include "widget/widgets.h"




// hooking
void * hooked = NULL;
static ClickFunc hook_click = NULL;
static DragFunc  hook_drag  = NULL;
static HoverFunc hook_hover = NULL;
static KeyFunc   hook_key   = NULL;

//					 label		x	 y	  w	  h
static WButton btn[] = {
	{"Hello!", 200, 300, 80, 20},
	{"World!", 300, 300, 80, 25},
	{"test==", 400, 300, 80, 30},
};




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




void event_click(int button, int state, int x, int y)
{
	if (hooked) {
		if (hook_click) hook_click(hooked, button, state, x, y);
		return;
	}

	int i;
	for (i=0; i<LEN(btn); i++)
		wbutton_click(&btn[i], button, state, x, y);
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

	int i;
	for (i=0; i<LEN(btn); i++)
		wbutton_hover(&btn[i], x, y);
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
	int i;
	for (i=0; i<LEN(btn); i++)
		wbutton_draw(&btn[i]);
}

