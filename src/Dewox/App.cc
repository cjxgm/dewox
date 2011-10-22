
#include "App.h"

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

	preview->resize(300, 300);
	preview->move(0, h - menubar->h - preview->h);

	vsplit->resize(4, preview->h);
	vsplit->move(preview->w, preview->y);

	properties->resize(w - preview->w - vsplit->w, preview->h);
	properties->move(preview->w + vsplit->w,
					h - menubar->h - properties->h);

	hsplit->resize(w, vsplit->w);
	hsplit->move(0, preview->y - hsplit->h);

	// stacking->move(0, 0);	// no need to move this.
	stacking->resize(w, h - menubar->h - preview->h - hsplit->h);
}

