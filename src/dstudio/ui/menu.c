
/************************************************************
 * dewox: menu.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "menu.h"
#include "../../dshared/dshared.h"
#include <GL/gl.h>

void ui_menu_draw(UIMenu menu[], int x, int y)
{
	int i;
	for (i=0; menu[i].type; i++) {
		switch (menu[i].type) {
			case UI_MENU_FUNC:
				glPointSize(1.0f);
				glColor3f(0.8f, 0.8f, 0.8f);
				font_render(menu[i].label, x+6, y+3);
				x += font_width(menu[i].label) + 12;
				break;
			default:
				break;
		}
	}
}

