
#ifndef __UI_HSPLIT__
#define __UI_HSPLIT__

#include "../UI.h"

class HSplit : public Button
{
public:
	HSplit(int x, int y, int w, int h)
		: Button(x, y, w, h) {}
	
	UIType getType() { return UI_TYPE_HSPLIT; }
	void paint();
	void onDrag   (int x, int y);
	void onPressed(int x, int y);
};

#endif

