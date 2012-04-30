
/************************************************************
 * dewox: a.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __LINK_H
#define __LINK_H




#define LINKABLE(TYPE)	\
	TYPE * prev; \
	TYPE * next;


// example:
// 		{ TRAVERSE(link, Type, p) {
// 			// do something with "p"
// 		}}
#define TRAVERSE(LNK, TYPE, V) \
	TYPE * V = (TYPE *)LNK; \
	while ((V = V->next) != (TYPE *)LNK)



typedef struct Link
{
	LINKABLE(struct Link);
}
Link;




void link_init(Link * lnk);
void link_addtail(Link * lnk, void * data);
void link_addhead(Link * lnk, void * data);
long link_length(Link * lnk);
void link_remove(void * data);
void link_delete(void * data);

#endif

