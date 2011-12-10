
#ifndef __FONT__
#define __FONT__

extern unsigned char font[256*16];

void draw_char(float x, float y, unsigned char ch);
void draw_string(float x, float y, float w,
		const char * str, float spacing);
void draw_string_centered(float x, float y, float w,
		const char * str, float spacing);

#endif

