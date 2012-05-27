
/************************************************************
 * dewox: operator.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __D_OPERATOR_H
#define __D_OPERATOR_H

typedef enum DType
{
	D_TYPE_VOID, D_TYPE_FLOAT, D_TYPE_VEC,
}
DType;

typedef enum DOperatorCategory
{
	D_OPERATOR_CATEGORY_UNKNOWN,
	D_OPERATOR_CATEGORY_SCENE,
	D_OPERATOR_CATEGORY_INSTR,
}
DOperatorCategory;

typedef enum DOperatorType
{
	D_OPERATOR_TYPE_MISC = 0,

	// scene
	D_OPERATOR_TYPE_TEXTURE = 1,
	D_OPERATOR_TYPE_MESH,
	D_OPERATOR_TYPE_OBJECT,

	// instrument
	D_OPERATOR_TYPE_OSC = 1,
	D_OPERATOR_TYPE_FX,
}
DOperatorType;

typedef struct DParam
{
	DType type;
	union {
		float f;
		float v[3];
	};
}
DParam;

typedef struct DParamMeta
{
	DType type;
	const char * name;
	void * p1, * p2, * p3, * p4;
}
DParamMeta;

typedef void (DOperatorPullFunc)(void * result, const DParam params[],
		const void * inputs[], int ninputs);

typedef struct DOperator
{
	const char * name;
	DOperatorCategory category;
	DOperatorType     type;
	const DOperatorPullFunc * pull;
	const DParamMeta * param;
}
DOperator;

typedef struct DNode
{
	int opid;		// operator id, for saving
	DParam * param;
	DOperator * op;
}
DNode;

void d_operator_register(const char * name, DParamMeta * param,
		DOperatorCategory category, DOperatorType type,
		DOperatorPullFunc pull);
DParam * d_operator_create_param_from_meta(DParamMeta * param);

#endif

