
#ifndef __UI_COLOR_MANAGER__
#define __UI_COLOR_MANAGER__

#include "RGB.h"

class ColorManager
{
public:
	RGB * fgLabel;
	RGB * bgButton1, * bgButton2;
	RGB * bgFrame, * focusFrameBorder, * unfocusFrameBorder;
	RGB * bgMenubar1, * bgMenubar2;

	ColorManager() :
		fgLabel(new RGB(0, 0, 0)),

		bgButton1(new RGB(150, 150, 150)),
		bgButton2(new RGB(100, 100, 100)),

		bgFrame(new RGB(140, 140, 140)),
		focusFrameBorder(new RGB(255, 255, 255)),
		unfocusFrameBorder(new RGB(128, 128, 128)),

		bgMenubar1(new RGB(128, 128, 150)),
		bgMenubar2(new RGB(100, 100, 120))
	{}
};

extern ColorManager colorManager;

#endif

