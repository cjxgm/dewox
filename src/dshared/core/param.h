
/************************************************************
 * dewox: param.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

// parameter relative functions
#ifndef __D_PARAM_H
#define __D_PARAM_H

typedef enum DType
{
	D_TYPE_DONE, D_TYPE_FLOAT, D_TYPE_VEC, D_TYPE_COLOR
}
DType;

typedef struct DParamMeta
{
	DType type;
	const char * name;
	float p1;	// `
	float p2;	// | They may have different meanings.
	float p3;	// |
	float p4;	// /
}
DParamMeta;

typedef struct DAnimFloat
{
	int enabled;
	float tf;		// time from
	float tt;		// time to
	float vf;		// value from
	float vt;		// value to
}
DAnimFloat;

typedef struct DAnimVec
{
	int enabled;
	float tf;		// time from
	float tt;		// time to
	float vf[3];	// value from
	float vt[3];	// value to
}
DAnimVec;

typedef struct DParam
{
	const DParamMeta * meta;
	union {
		float f;		// float
		float v[3];		// vector
	};
	union {
		DAnimFloat af;		// animation float
		DAnimVec   av;		// animation vector
	};
}
DParam;

extern DParam * d_active_param;

DParam * d_create_param_from_meta(const DParamMeta * param);

#endif

