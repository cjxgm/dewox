
#ifndef __UI_RGB__
#define __UI_RGB__

class RGB
{
public:
	unsigned char r, g, b;

	RGB() : r(0), g(0), b(0) {}
	RGB(unsigned char r, unsigned char g, unsigned char b)
		: r(r), g(g), b(b) {}

	void apply();
};

#endif

