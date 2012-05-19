
/************************************************************
 * dewox: erp.c: intERPolation
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "erp.h"

// Name this as: [df dt]
inline float lerp(float v, float vf, float vt, float df, float dt)
{
	return (v-vf) / (vt-vf) * (dt-df) + df;
}




// [df [df dt]]: named as [*df dt]
float ferp_in(float v, float vf, float vt, float df, float dt)
{
	return lerp(v, vf, vt, df, lerp(v, vf, vt, df, dt));
}

// [[df dt] dt]: named as [df dt*]
float ferp_out(float v, float vf, float vt, float df, float dt)
{
	return lerp(v, vf, vt, lerp(v, vf, vt, df, dt), dt);
}

// [[*df dt] [df dt*]]: named as [*df dt*]
float ferp(float v, float vf, float vt, float df, float dt)
{
	return lerp(v, vf, vt,
			ferp_in(v, vf, vt, df, dt),
			ferp_out(v, vf, vt, df, dt));
}

