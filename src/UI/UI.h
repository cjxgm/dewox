
#ifndef __UI__
#define __UI__

#include "../Util/List.h"
#include "RGB.h"
#include "ColorManager.h"
#include <GL/gl.h>
#include <string>
using namespace std;

typedef enum UIType
{
	UI_TYPE_APP,
	UI_TYPE_FRAME,
	UI_TYPE_LABEL,
	UI_TYPE_BUTTON,
	UI_TYPE_VSPLIT,
	UI_TYPE_HSPLIT,
	UI_TYPE_MENUBAR,
}
UIType;

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
};

#include "Widget/Label.h"
#include "Widget/Button.h"
#include "Widget/Frame.h"
#include "Widget/VSplit.h"
#include "Widget/HSplit.h"
#include "Widget/Menubar.h"

#endif

