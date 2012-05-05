
/************************************************************
 * dewox: menu.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __MENU_H
#define __MENU_H


#define UI_MENU_DONE					0
#define UI_MENU_FUNC					1
#define UI_MENU_EDITOR_SELECTOR			2
typedef struct UIMenu
{
	int type;
	void * data;
	const char * label;
}
UIMenu;

typedef struct UIMenuParam
{
	int active;
}
UIMenuParam;


void ui_menu_draw(UIMenu menu[], UIMenuParam * param, int x, int y);
void ui_menu_hover(UIMenu menu[], UIMenuParam * param,
		int x, int y, int mx, int my);
void ui_menu_click(UIMenu menu[], UIMenuParam * param,
		int x, int y, int mx, int my);

#endif

