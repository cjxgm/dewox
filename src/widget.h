
#ifndef __WIDGET__
#define __WIDGET__




typedef enum
{
	WSTYLE_NORMAL,
	WSTYLE_HOVERED,
	WSTYLE_DRAGGING,
	WSTYLE_SELECTED,
} WStyle;




// pager widgets

void draw_page_button(const char * label, int x, int y,
		int w, int h, WStyle style);




// -- split
// ::: Split/divide an area into 2 parts.

// horizontal or vertical
typedef enum { WSPLIT_HOR, WSPLIT_VERT } WSplitType;

typedef struct WSplit
{
	WSplitType type;
// for SPLIT_HOR,  low & high means left and right
// for SPLIT_VERT, low & high means top  and bottom
	int low, high;
	int value;

	WStyle style;
	int tmp;
}
WSplit;

void draw_split(WSplit * widget);
void hover_split(WSplit * widget, int x, int y);
void drag_split (WSplit * widget, int x, int y);
void click_split(WSplit * widget, int button, int state, int x, int y);




// hover tests
int hovertest_box(int mx, int my, int x, int y, int w, int h);

#endif

