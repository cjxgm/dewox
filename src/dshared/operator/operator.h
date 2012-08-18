
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

#include "../core/param.h"

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

typedef void * DOperatorPullFunc;
typedef void * DTex;
typedef void (DOperatorPullFuncTex)(DTex result, const DParam params[],
		const DTex inputs[], int ninputs);

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
	const DOperator * op;
}
DNode;

void d_operator_register(const char * name, const DParamMeta * param,
		const DOperatorCategory category, const DOperatorType type,
		const DOperatorPullFunc pull);

#endif

