
#ifndef __UI__
#define __UI__

#include "../Util/List.h"
#include "../Util/Log.h"
#include "RGB.h"
#include "ColorManager.h"
#include <GL/gl.h>
#include <string>
using namespace std;

enum UIType
{
	UI_TYPE_APP,
	UI_TYPE_FRAME,
	UI_TYPE_LABEL,
	UI_TYPE_BUTTON,
	UI_TYPE_VSPLIT,
	UI_TYPE_HSPLIT,
	UI_TYPE_MENUBAR,
};

enum MouseEventType
{
	MOUSE_MOVE,
	MOUSE_DOWN,
	MOUSE_UP,
	MOUSE_CLICK,
};

enum MouseButtonType
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
};

enum KeyEventType
{
	KEY_DOWN,
	KEY_UP,
	KEY_PRESSED,
};

#define KEY_ALT		(1<<0)
#define KEY_CTRL	(1<<1)
#define KEY_SHIFT	(1<<2)

class UI
{
public:
	int x, y, w, h;
	bool hidden;

	UI(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h), hidden(0) {}

	virtual void paint() = 0;
	virtual UIType getType() = 0;

	virtual void resize(int w, int h)
	{
		this->w = w;
		this->h = h;
	}

	virtual void move(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	virtual void mouseEvent(MouseEventType t,
							MouseButtonType b,
							int x, int y) {}
	virtual void keyEvent  (KeyEventType t,
							int keycode,
							int modifier) {}
};

#include "EventManager.h"
#include "Widget/Label.h"
#include "Widget/Button.h"
#include "Widget/Frame.h"
#include "Widget/VSplit.h"
#include "Widget/HSplit.h"
#include "Widget/Menubar.h"

#endif

