
#ifndef __LIST__
#define __LIST__

//============================================================
// It's just a double-directional circled link
typedef struct list LIST;
struct list
{
	LIST * prev;
	LIST * next;
	void * data;
};

//============================================================
// This function will create a list's root.
// If you want to create a list node,
// use LIST * lst = NEW(LIST) for it.
LIST * list_new();

//============================================================
// This function will append <src> to <dst>
// It's no need that <dst> is a root list.
void list_append(LIST * dst, LIST * src);

//============================================================
// This macro will prepend <src> to <dst>
// It's no need that <dst> is a root list.
#define list_prepend(dst, src)	list_append((dst)->prev, src)

//============================================================
// This function will remove <src> out of the list which
// contains it without freeing it.
void list_remove(LIST * src);

//============================================================
// This macro will do a type casting for getting the data in
// the list.
#define list_get(lst, type)		((type)((lst)->data))

//============================================================
// Q: Why there is nothing about freeing a list?
// A: the struct list contains a field called <data>, it's set
//    to "void *". So when you free a list, the <data> can not
//    be freed correctly. It may cause memory overflow. SO,
//    AFTER REMOVING A LIST, YOU MUST FREE IT BY YOURSELF, OR
//    THEY WON'T DISAPPER FROM THE MEMORY!

#endif

