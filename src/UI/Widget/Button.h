
#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "../UI.h"

class Button : public UI
{
public:
	Label * label;
	bool pressed;

	Button(int x, int y, int w, int h, string text):
		UI(x, y, w, h),
		label(new Label(0, 0, 0, 0, text)),
		pressed(false)
	{
		eventManager.listenMouse(this);
	}
	Button(int x, int y, int w, int h) :
		UI(x, y, w, h),
		label(new Label(0, 0, 0, 0, "")),
		pressed(false)
	{
		eventManager.listenMouse(this);
	}
	
	~Button() { delete label; }

	UIType getType() { return UI_TYPE_BUTTON; }
	void paint();
	void resize(int w, int h);
	void mouseEvent(MouseEventType t, MouseButtonType b, int x, int y);

	virtual void onDrag   (int x, int y) {}
	virtual void onPressed(int x, int y) {}
};

#endif

