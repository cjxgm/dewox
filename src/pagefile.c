
#include "pagefile.h"
#include "pager.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

void pagefile_init()
{
	pages[PAGE_FILE] = (page){
		"file", NULL, NULL, NULL, NULL, NULL
	};
}

