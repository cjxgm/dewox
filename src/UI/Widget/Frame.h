
#ifndef __UI_FRAME__
#define __UI_FRAME__

#include "../UI.h"

class Frame : public UI
{
public:
	bool focused;

	Frame(int x, int y, int w, int h)
		: UI(x, y, w, h), focused(false)
	{
		eventManager.listenMouse(this);
	}
	
	UIType getType() { return UI_TYPE_FRAME; }
	void paint();
	void mouseEvent(MouseEventType t, MouseButtonType b, int x, int y);
};

#endif

