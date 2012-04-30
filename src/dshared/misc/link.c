
/************************************************************
 * dewox: a.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "link.h"
#include <stdlib.h>

void link_init(Link * lnk)
{
	lnk->prev = lnk->next = lnk;
}

void link_addtail(Link * lnk, void * data)
{
	link_addhead(lnk->prev, data);
}

void link_addhead(Link * lnk, void * data)
{
	Link * t = data;
	t->prev = lnk;
	t->next = lnk->next;
	lnk->next->prev = t;
	lnk->next = t;
}

long link_length(Link * lnk)
{
	long len = 0;
	{ TRAVERSE(lnk, Link, p) len++; }
	return len;
}

void link_remove(void * data)
{
	Link * t = data;
	t->prev->next = t->next;
	t->next->prev = t->prev;
}

void link_delete(void * data)
{
	link_remove(data);
	free(data);
}

