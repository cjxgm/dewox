
#ifndef __UI_LABEL__
#define __UI_LABEL__

#include "../ui.h"

struct ui_label
{
	UI ui;
	const char * text;
	float r, g, b;
};

// DO NOT FREE OR CHANGE THE TEXT GIVEN TO THIS!
void ui_label_init(UI_LABEL * lb, int x, int y, int w, int h,
					const char * text);

#endif

