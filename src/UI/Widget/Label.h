
#ifndef __UI_LABEL__
#define __UI_LABEL__

#include "../UI.h"

class Label : public UI
{
public:
	string text;
	RGB color;

	Label(int x, int y, int w, int h, string text)
		: UI(x, y, w, h), text(text), color(RGB(0, 0, 0)) {}
	Label(int x, int y, int w, int h, string text, RGB color)
		: UI(x, y, w, h), text(text), color(color) {}
	
	UIType getType() { return UI_TYPE_LABEL; }
	void paint();
};

#endif

