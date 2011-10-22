
#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "../UI.h"

class Button : public UI
{
public:
	Label * label;

	Button(int x, int y, int w, int h) :
		UI(x, y, w, h),
		label(new Label(0, 0, 0, 0, ""))
	{}
	Button(int x, int y, int w, int h, string text):
		UI(x, y, w, h),
		label(new Label(0, 0, 0, 0, text))
	{}
	
	~Button() { delete label; }

	UIType getType() { return UI_TYPE_BUTTON; }
	void paint();
	void resize(int w, int h);
};

#endif

