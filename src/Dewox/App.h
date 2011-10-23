
#ifndef __APP__
#define __APP__

#include "../UI/UI.h"

extern string dw_file;

class App : public UI
{
public:
	App(int x, int y, int w, int h)
		: UI(x, y, w, h),
		preview(new Frame(0, 0, 0, 0)),
		properties(new Frame(0, 0, 0, 0)),
		stacking(new Frame(0, 0, 0, 0)),

		hsplit(new HSplit(0, 0, 0, 0)),
		vsplit(new VSplit(0, 0, 0, 0)),

		menubar(new Menubar(0, 0, 0, 0, MENUBAR_H)),
		btnSave(new Button(0, 0, 0, 0, "Save")),
		lbFilename(new Label(0, 0, 0, 0, dw_file))
	{
		eventManager.listenKey(this);
		menubar->add(btnSave);
		menubar->add(lbFilename);
	}

	UIType getType() { return UI_TYPE_APP; }
	void paint();
	void resize(int w, int h);
	void keyEvent(KeyEventType t, int keycode, int modifier);
	void update();

private:
	Frame * preview;
	Frame * properties;
	Frame * stacking;
	HSplit * hsplit;
	VSplit * vsplit;

	Menubar * menubar;
	Button  * btnSave;
	Label   * lbFilename;
};

#endif

