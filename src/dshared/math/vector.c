
/************************************************************
 * dewox: vector.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "vector.h"
#include <math.h>

// note: "a>" means vector a, while "a" means scaler a

/* vec_add(vd, v1, v2)
 * 		vd> = v1> + v2>
 *
 * vec_addv(vd, v)
 * 		vd> = vd> + v>
 */
void vec_add(float vd[3], float v1[3], float v2[3])
{
	vd[0] = v1[0] + v2[0];
	vd[1] = v1[1] + v2[1];
	vd[2] = v1[2] + v2[2];
}

void vec_addv(float vd[3], float v[3])
{
	vd[0] += v[0];
	vd[1] += v[1];
	vd[2] += v[2];
}


/* vec_sub(vd, v1, v2)
 * 		vd> = v1> - v2>
 *
 * vec_subv(vd, v)
 * 		vd> = vd> - v>
 */
void vec_sub(float vd[3], float v1[3], float v2[3])
{
	vd[0] = v1[0] - v2[0];
	vd[1] = v1[1] - v2[1];
	vd[2] = v1[2] - v2[2];
}

void vec_subv(float vd[3], float v[3])
{
	vd[0] -= v[0];
	vd[1] -= v[1];
	vd[2] -= v[2];
}


/* vec_mul(vd, v, s)
 * 		vd> = s * v>
 *
 * vec_mulv(vd, s)
 * 		vd> = s * vd>
 */
void vec_mul(float vd[3], float v[3], float s)
{
	vd[0] = v[0] * s;
	vd[1] = v[1] * s;
	vd[2] = v[2] * s;
}

void vec_mulv(float vd[3], float s)
{
	vd[0] *= s;
	vd[1] *= s;
	vd[2] *= s;
}


/* s = vec_dot(v1, v2)
 * 		s = v1> . v2> = |v1>||v2>|cos[a], where [a] is the angle
 * 		constructed by v1> and v2> sharing the same origin.
 *
 * vec_cross(vd, v1, v2)
 * 		vd> = v1> X v2>
 *
 * 		vd> is the vector perpendicular to the surface constructed by
 * 		v1> and v2>.
 *
 * 		NOTE: There's no "vec_crossv"!
 */
float vec_dot(float v1[3], float v2[3])
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void vec_cross(float vd[3], float v1[3], float v2[3])
{
	vd[0] = v1[1]*v2[2] - v2[1]*v1[2];
	vd[1] = v1[2]*v2[0] - v2[2]*v1[0];
	vd[2] = v1[0]*v2[1] - v2[0]*v1[1];
}


/* s = vec_sqr(v)
 * 		s = v> ^ 2 = v> . v>
 *
 * s = vec_mod(v)
 * 		s = |v>| = sqrt(v> ^ 2)
 *		This calculates the modulos(length) of v>.
 */
float vec_sqr(float v[3])
{
	return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}

float vec_mod(float v[3])
{
	return sqrtf(vec_sqr(v));
}


/* vec_norm(vd, v)
 * 		vd> = (1 / |v>|) * v>
 *
 * vec_normv(v)
 * 		v> = (1 / |v>|) * v>
 *
 * Normalize v>, or we say make it unit-length.
 */
void vec_norm(float vd[3], float v[3])
{
	vec_mul(vd, v, 1.0f / vec_mod(v));
}

void vec_normv(float vd[3])
{
	vec_mulv(vd, 1.0f / vec_mod(vd));
}


/* vec_unit_normal(vd, v1, v2)
 * 		vd> = (1 / |v1> X v2>|) * (v1> X v2>)
 *
 * Calculate the unit-length normal of a surface, which is the vector
 * perpendicular to the surface constructed by v1> and v2>.
 *
 * vec_unit_normal_3p(vd, p1, p2, p3)
 * 		vec_unit_normal(vd>, p2> - p1>, p3> - p1>)
 *
 * Calculate the unit-length normal of a surface, which is the vector
 * perpendicular to the surface constructed by 3 points.
 *
 *
 * vec_cpy(vd, v)
 * 		vd> = v>
 */
void vec_unit_normal(float vd[3], float v1[3], float v2[3])
{
	vec_cross(vd, v1, v2);
	vec_normv(vd);
}

void vec_unit_normal_3p(float vd[3], float p1[3], float p2[3], float p3[3])
{
	float v[2][3];
	vec_sub(v[0], p2, p1);
	vec_sub(v[1], p3, p1);
	vec_unit_normal(vd, v[0], v[1]);
}

void vec_cpy(float vd[3], float v[3])
{
	vd[0] = v[0];
	vd[1] = v[1];
	vd[2] = v[2];
}


/* vec_lirp(vd, ratio, df, dt)
 * 		vd> = (1-ratio) * df> + ratio * dt>
 *
 * Vector linear interpolation. The larger ratio is, the more dt is.
 */
void vec_lerp(float vd[3], float ratio, float df[3], float dt[3])
{
	float v[2][3];
	vec_mul(v[0], df, 1-ratio);
	vec_mul(v[1], dt,   ratio);
	vec_add(vd, v[0], v[1]);
}

