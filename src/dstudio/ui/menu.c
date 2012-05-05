
/************************************************************
 * dewox: menu.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "menu.h"
#include "../wm.h"
#include "../../dshared/dshared.h"
#include <GL/gl.h>

void ui_menu_draw(UIMenu menu[], UIMenuParam * param, int x, int y)
{
	int i, w;
	for (i=0; menu[i].type; i++) {
		switch (menu[i].type) {
			case UI_MENU_FUNC:
				w = font_width(menu[i].label);
				if (i == param->active) {
					glColor3f(0.2f, 0.2f, 1.0f);
					glBegin(GL_QUADS);
					glVertex2f(x+2, y+3);
					glVertex2f(x+w+12, y+3);
					glVertex2f(x+w+12, y+25-3);
					glVertex2f(x+2, y+25-3);
					glEnd();
					glColor3f(0.0f, 0.0f, 0.0f);
				}
				else glColor3f(0.8f, 0.8f, 0.8f);
				glPointSize(1.0f);
				font_render(menu[i].label, x+6, y+3);
				x += w + 12;
				break;
			default:
				break;
		}
	}
}

void ui_menu_hover(UIMenu menu[], UIMenuParam * param,
		int x, int y, int mx, int my)
{
	int i, w;
	for (i=0; menu[i].type; i++) {
		if (my <= y+3 || my >= y+25-3) {
			if (param->active != -1) {
				param->active = -1;
				wm_require_refresh();
			}
			continue;
		}

		switch (menu[i].type) {
			case UI_MENU_FUNC:
				w = font_width(menu[i].label);
				if (mx > x+2 && mx < x+w+12) {
					if (param->active != i) {
						param->active = i;
						wm_require_refresh();
					}
					return;
				}
				x += w + 12;
				break;
			default:
				break;
		}
	}
	if (param->active) {
		param->active = -1;
		wm_require_refresh();
	}
}

