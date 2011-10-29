
#ifndef __FONT__
#define __FONT__

extern unsigned char font[256*16];

void draw_char(int x, int y, unsigned char ch);
void draw_string(int x, int y, int w, const char * str, int spacing);
void draw_string_centered(int x, int y, int w,
		const char * str, int spacing);

#endif

