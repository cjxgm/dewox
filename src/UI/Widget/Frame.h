
#ifndef __UI_FRAME__
#define __UI_FRAME__

#include "../UI.h"

class Frame : public UI
{
public:
	Frame(int x, int y, int w, int h)
		: UI(x, y, w, h) {}
	
	UIType getType() { return UI_TYPE_FRAME; }
	void paint();
};

#endif

