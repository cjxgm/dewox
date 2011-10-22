
#ifndef __UI__
#define __UI__

#include "../Util/List.h"
#include "RGB.h"
#include <GL/gl.h>
#include <string>
using namespace std;

typedef enum UIType
{
	UI_TYPE_UNKNOWN,
	UI_TYPE_LABEL,
	UI_TYPE_BUTTON,
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

#endif

