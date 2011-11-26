
#ifndef __EVENT__
#define __EVENT__


typedef void (*ClickFunc)(void * w, int button, int state, int x, int y);
typedef void (*DragFunc) (void * w, int x, int y);
typedef void (*HoverFunc)(void * w, int x, int y);
typedef void (*KeyFunc)  (void * w, unsigned char k);


extern void * hooked;
void hook(void * widget, ClickFunc click,
			DragFunc drag, HoverFunc hover, KeyFunc key);
void unhook();


void event_click(int button, int state, int x, int y);
void event_drag(int x, int y);
void event_hover(int x, int y);
void event_key(unsigned char k);
void event_draw(int w, int h);

#endif

