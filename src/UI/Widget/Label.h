
#ifndef __UI_LABEL__
#define __UI_LABEL__

#include "../UI.h"

class Label : public UI
{
public:
	string text;

	Label(int x, int y, int w, int h, string text)
		: UI(x, y, w, h), text(text) {}

	UIType getType() { return UI_TYPE_LABEL; }
	void paint();
};

#endif

