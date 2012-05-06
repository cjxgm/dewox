
/************************************************************
 * dewox: irp.h: InteRPolation
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __IRP_H
#define __IRP_H

// Linear InteRPolation
inline float lirp(float v, float vf, float vt, float df, float dt);

// Fine InteRPolation
float firp(float v, float vf, float vt, float df, float dt);
// with smooth in/out seperately.
float firp_in(float v, float vf, float vt, float df, float dt);
float firp_out(float v, float vf, float vt, float df, float dt);

#endif

