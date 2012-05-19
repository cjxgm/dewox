
/************************************************************
 * dewox: erp.h: intERPolation
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __D_ERP_H
#define __D_ERP_H

// Linear intERPolation
inline float lerp(float v, float vf, float vt, float df, float dt);

// Fine intERPolation
float ferp(float v, float vf, float vt, float df, float dt);
// with smooth in/out seperately.
float ferp_in(float v, float vf, float vt, float df, float dt);
float ferp_out(float v, float vf, float vt, float df, float dt);

#endif

