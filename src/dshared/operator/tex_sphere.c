
/************************************************************
 * dewox: tex_sphere.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#if 0

#include "operator_decl.h"

static DParamMeta param[] = {
	//              label       x      y       z
	{D_TYPE_VEC  , "Center", 128.0f, 128.0f, 128.0f},
	//              label  value  min    max     step
	{D_TYPE_FLOAT, "Radius", 30, 0.0f, 65536.0f, 1.0f},
	//              label    r     g     b
	{D_TYPE_COLOR, "Color", 1.0f, 1.0f, 1.0f},
	{D_TYPE_DONE}
};

void d_operator_tex_sphere_init()
{
	REGISTER_OPERATOR("Sphere",
			D_OPERATOR_CATEGORY_SCENE,
			D_OPERATOR_TYPE_TEXTURE);
}

static int pull(DTex result, const DParam params[],
		const DTex inputs[], int ninputs)
{
	float * center = params[0].v;	// v = vector3
	float   radius = params[1].f;	// f = float
	float * color  = params[2].v;	// v = vector3

	unsigned char x, y;
	for (y=0; y<256; y++)
		for (x=0; x<256; x++) {
			int dx = x-center[0];
			int dy = y-center[1];
			int ds = dx*dx + dy*dy;
			int dr = radius * radius;
			if (ds > dr) continue;
			float a = 1.0f - (float)ds / (float)dr;
			vec_mul(result[(y<<8)|x], color, a);
		}
	
	return 0;	// no errors
}

#endif

