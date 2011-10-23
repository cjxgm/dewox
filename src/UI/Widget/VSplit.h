
#ifndef __UI_VSPLIT__
#define __UI_VSPLIT__

#include "../UI.h"

class VSplit : public Button
{
public:
	VSplit(int x, int y, int w, int h)
		: Button(x, y, w, h) {}
	
	UIType getType() { return UI_TYPE_VSPLIT; }
	void paint();
	void onDrag   (int x, int y);
	void onPressed(int x, int y);
};

#endif

