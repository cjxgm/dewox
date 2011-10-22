
#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "../ui.h"

struct ui_button
{
	UI ui;
	UI_LABEL * label;
};

void ui_button_init(UI_BUTTON * btn, int x, int y, int w, int h,
					const char * text);

#endif

