
#include "widget.h"

int hovertest_box(int mx, int my, int x, int y, int w, int h)
{
	return ((mx > x && mx < x+w) && (my > y && my < y+h));
}

