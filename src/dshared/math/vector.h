
/************************************************************
 * dewox: vector.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __D_VECTOR_H
#define __D_VECTOR_H

void vec_add(float vd[3], float v1[3], float v2[3]);
void vec_addv(float vd[3], float v[3]);

void vec_sub(float vd[3], float v1[3], float v2[3]);
void vec_subv(float vd[3], float v[3]);

void vec_mul(float vd[3], float v[3], float s);
void vec_mulv(float vd[3], float s);

float vec_dot(float v1[3], float v2[3]);
void vec_cross(float vd[3], float v1[3], float v2[3]);

float vec_sqr(float v[3]);
float vec_mod(float v[3]);

void vec_norm(float vd[3], float v[3]);
void vec_normv(float vd[3]);

void vec_unit_normal(float vd[3], float v1[3], float v2[3]);
void vec_unit_normal_3p(float vd[3], float p1[3], float p2[3], float p3[3]);
void vec_cpy(float vd[3], float v[3]);

void vec_lerp(float vd[3], float ratio, float df[3], float dt[3]);

#endif

