
#include "info.h"
#include "../../dui/config.h"
#include "../../dutil/dutil.h"
#include "../../dui/widget/widgets.h"

static WButton btns[] = {
	{18, 18, 0, 20, "Name: "     APPNAME   },
	{18, 42, 0, 20, "Ver: "      APPVER    },
	{18, 66, 0, 20, "Author(s): "APPAUTHORS},
	{18, 90, 0, 20, "Inspired by: .werkkzeug, Komposter, Blender"},
};

void info_click(int button, int state, int x, int y)
{
	int i;
	for (i=0; i<LEN(btns); i++)
		wbutton_click(&btns[i], button, state, x, y);
}

void info_drag(int x, int y)
{
}

void info_hover(int x, int y)
{
	int i;
	for (i=0; i<LEN(btns); i++)
		wbutton_hover(&btns[i], x, y);
}

void info_key(unsigned char k)
{
}

void info_draw(int w, int h)
{
	int i;
	for (i=0; i<LEN(btns); i++) {
		btns[i].w = w - 36;
		wbutton_draw(&btns[i]);
	}
	draw_border(10, 10, w-20, h-10);
}

