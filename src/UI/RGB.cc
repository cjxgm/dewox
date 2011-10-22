
#include "RGB.h"
#include <GL/gl.h>

void RGB::apply()
{
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
}

