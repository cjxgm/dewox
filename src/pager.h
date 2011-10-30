
#ifndef __PAGER__
#define __PAGER__

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef struct
{
	const char * name;
	void (*click)(int button, int state, int x, int y);
	void (*drag)(int x, int y);
	void (*hover)(int x, int y);
	void (*key)(unsigned char k, int x, int y);
	void (*draw)();
	int hovered;
}
page;

#define PAGE_FILE		0
#define PAGE_SCENE		1
#define PAGE_TRACK		2
#define PAGE_CONFIG		3
#define PAGE_SIZE		2	// TODO!
extern page pages[PAGE_SIZE];
extern int  cpage;

void pager_click(int button, int state, int x, int y);
void pager_hover(int x, int y);
void pager_draw();

#endif

