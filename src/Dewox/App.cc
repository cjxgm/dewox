
#include "App.h"
#include <cstdlib>
using namespace std;

void App::paint()
{
	menubar->paint();
	preview->paint();
	properties->paint();
	stacking->paint();
	hsplit->paint();
	vsplit->paint();
}

void App::resize(int w, int h)
{
	UI::resize(w, h);

	menubar->resize(w, 20);
	menubar->move(0, h - menubar->h);

	btnSave->resize((btnSave->label->text.length() + 2) * 10, menubar->h);
	//btnSave->move(0, 0);

	preview->resize(300, 300);
	preview->move(0, h - menubar->h - preview->h - 1);

	vsplit->resize(4, preview->h + 1);
	vsplit->move(preview->w, preview->y);

	properties->resize(w - preview->w - vsplit->w - 1, preview->h);
	properties->move(preview->w + vsplit->w + 1, preview->y);

	hsplit->resize(w, vsplit->w);
	hsplit->move(0, preview->y - hsplit->h);

	stacking->resize(w, hsplit->y - 1);
	// stacking->move(0, 0);	// no need to move this.
}

void App::keyEvent(KeyEventType t, int keycode, int modifier)
{
	switch ((int)t) {
		case KEY_PRESSED:
			if (keycode == 27)
				exit(0);
			break;
	}
}

