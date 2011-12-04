
#ifndef __EVENT__
#define __EVENT__


typedef void (*ClickFunc)(void * w, int button, int state, int x, int y);
typedef void (*DragFunc) (void * w, int x, int y);
typedef void (*HoverFunc)(void * w, int x, int y);
typedef void (*KeyFunc)  (void * w, unsigned char k);
typedef void (*ActFunc)  (void * w);


extern void * hooked;
void hook(void * widget, ClickFunc click,
			DragFunc drag, HoverFunc hover, KeyFunc key);
void unhook();


void msgbox(void * widget, ActFunc act,
		const char * title, const char * label);


void event_click(int button, int state, int x, int y);
void event_drag (int x, int y);
void event_hover(int x, int y);
void event_key  (unsigned char k);
void event_draw (int w, int h);


// Implemented in OTHER file. For now, dewox.c
void app_click(int button, int state, int x, int y);
void app_drag (int x, int y);
void app_hover(int x, int y);
void app_key  (unsigned char k);
void app_draw (int w, int h);

#endif

