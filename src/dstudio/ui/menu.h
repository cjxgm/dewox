
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
	void * param;
	const char * label;
}
UIMenu;


void ui_menu_draw(UIMenu menu[], int x, int y);

#endif

