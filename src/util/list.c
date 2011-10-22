
#include "list.h"
#include "util.h"

LIST * list_new()
{
	LIST * lst = NEW(LIST);
	lst->prev = lst->next = lst;
	lst->data = NULL;

	return lst;
}

void list_append(LIST * dst, LIST * src)
{
	src->prev = dst->prev;
	src->next = dst;
	dst->prev->next = src;
	dst->prev = src;
}

void list_remove(LIST * src)
{
	src->prev->next = src->next;
	src->next->prev = src->prev;
}

