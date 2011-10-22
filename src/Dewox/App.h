
#ifndef __APP__
#define __APP__

#include "../UI/UI.h"

class App : public UI
{
public:
	App(int x, int y, int w, int h)
		: UI(x, y, w, h),
		menubar(new Frame(0, 0, 0, 0)),
		preview(new Frame(0, 0, 0, 0)),
		properties(new Frame(0, 0, 0, 0)),
		stacking(new Frame(0, 0, 0, 0)),
		hsplit(new HSplit(0, 0, 0, 0)),
		vsplit(new VSplit(0, 0, 0, 0))
	{}

	UIType getType() { return UI_TYPE_APP; }
	void paint();
	void resize(int w, int h);

private:
	Frame * menubar;
	Frame * preview;
	Frame * properties;
	Frame * stacking;
	HSplit * hsplit;
	VSplit * vsplit;
};

#endif

