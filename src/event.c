
#include <string.h>

#include "event.h"
#include "common.h"
#include "window.h"
#include "widget/widget.h"




static int mousex, mousey;

// hooking
void * hooked = NULL;
static ClickFunc hook_click = NULL;
static DragFunc  hook_drag  = NULL;
static HoverFunc hook_hover = NULL;
static KeyFunc   hook_key   = NULL;

// msgbox
void * msg_widget = NULL;
static const char * msg_title = NULL;
static const char * msg_label = NULL;
static ActFunc msg_act = NULL;

static WState msg_state;
static float  msgx, msgy, msgw;

static void msg_click(void * w, int button, int state, int x, int y);
static void msg_hover(void * w, int x, int y);
static void msg_key  (void * w, unsigned char k);




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




void msgbox(void * widget, ActFunc act,
		const char * title, const char * label)
{
	msg_title = title;
	msg_label = label;
	msg_act   = act;

	int w1 = strlen(title)*8 + 4;
	int w2 = strlen(label)*8 + 20;
	msgw = (w1>w2 ? w1 : w2) + 30;
	if (msgw < 100) msgw = 100;

	msgx = mousex - msgw + 20;
	msgy = mousey - 30;
	if (msgx < 0) msgx = 0;
	if (msgy < 0) msgy = 0;
	msg_hover(NULL, mousex, mousey);

	hook(widget, (ClickFunc)&msg_click, (DragFunc)&msg_hover,
				 (HoverFunc)&msg_hover, (KeyFunc) &msg_key);
	msg_widget = widget;
}

static void msg_click(void * w, int button, int state, int x, int y)
{
	if (!hovertest_box(x, y, msgx, msgy, msgw, 40)) {
		msg_widget = NULL;
		unhook();
		return;
	}
	if (button == MOUSE_LEFT && state == MOUSE_UP
		&& msg_state == WSTATE_HOVERED && msg_act)
		msg_act(w);
}

static void msg_hover(void * w, int x, int y)
{
	if (!hovertest_box(x, y, msgx, msgy, msgw, 40)) {
		msg_widget = NULL;
		unhook();
		return;
	}
	msg_state = (hovertest_box(x, y, msgx+2, msgy+20, msgw-4, 18) ?
					WSTATE_HOVERED : WSTATE_NORMAL);
}

static void msg_key(void * w, unsigned char k)
{
	if (msg_act && (k == '\r' || k == '\n' || k == ' ' || k == '\t'))
		msg_act(w);
	else {
		msg_widget = NULL;
		unhook();
	}
}




void event_click(int button, int state, int x, int y)
{
	if (hooked) {
		if (hook_click) hook_click(hooked, button, state, x, y);
		return;
	}
	app_click(button, state, x, y);
}

void event_drag(int x, int y)
{
	mousex = x;
	mousey = y;

	if (hooked) {
		if (hook_drag) hook_drag(hooked, x, y);
		return;
	}
	app_drag(x, y);
}

void event_hover(int x, int y)
{
	mousex = x;
	mousey = y;

	if (hooked) {
		if (hook_hover) hook_hover(hooked, x, y);
		return;
	}
	app_hover(x, y);
}

void event_key(unsigned char k)
{
	if (hooked) {
		if (hook_key) hook_key(hooked, k);
		return;
	}
	app_key(k);
}

void event_draw(int w, int h)
{
	app_draw(w, h);

	if (msg_widget)
		draw_msgbox(msgx, msgy, msgw, msg_title, msg_label, msg_state);
}

