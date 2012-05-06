
/************************************************************
 * dewox: irp.c: InteRPolation
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "irp.h"

// Name this as: [df dt]
inline float lirp(float v, float vf, float vt, float df, float dt)
{
	return (v-vf) / (vt-vf) * (dt-df) + df;
}




// [df [df dt]]: named as [*df dt]
float firp_in(float v, float vf, float vt, float df, float dt)
{
	return lirp(v, vf, vt, df, lirp(v, vf, vt, df, dt));
}

// [[df dt] dt]: named as [df dt*]
float firp_out(float v, float vf, float vt, float df, float dt)
{
	return lirp(v, vf, vt, lirp(v, vf, vt, df, dt), dt);
}

// [[*df dt] [df dt*]]: named as [*df dt*]
float firp(float v, float vf, float vt, float df, float dt)
{
	return lirp(v, vf, vt,
			firp_in(v, vf, vt, df, dt),
			firp_out(v, vf, vt, df, dt));
}

