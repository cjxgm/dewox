
/************************************************************
 * dewox: cmenu.h
 * Chained Menu
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __CMENU_H
#define __CMENU_H


#define CMENU_STACK_SIZE		8
#define CMENU_ITEM_SIZE			32


typedef void (CMenuCallback)(void * data);

typedef struct CMenuItem
{
	const char * name;			// text shown in menu
	int key;					// shortcut key
	CMenuCallback * callback;	// NULL for submenu
	void * data;				// when above is NULL, this stores submenu
}
CMenuItem;

typedef struct CMenuSub
{
	CMenuItem items[CMENU_ITEM_SIZE];
	int size;	// how many items are used
	int w;		// max width
}
CMenuSub;

typedef struct CMenuStack
{
	CMenuSub * sub;
	int selected;	// -1 for not selecting anything
}
CMenuStack;

typedef struct CMenu
{
	CMenuSub * sub;
	CMenuStack stack[CMENU_STACK_SIZE];
	int sp;
	float w;
	float h;
	float neww;
	float newh;
}
CMenu;


CMenu * cmenu_create();
void * cmenu_sub_add(CMenuSub * sub, const char * name, int key,
		CMenuCallback * callback, void * data);
void cmenu_show(CMenu * menu, float x, float y);
CMenuItem * cmenu_sub_find(CMenuSub * sub, const char * name);


#endif

