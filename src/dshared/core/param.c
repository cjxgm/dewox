
/************************************************************
 * dewox: param.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "param.h"
#include "core.h"

DParam * d_active_param;

DParam * d_create_param_from_meta(const DParamMeta * param)
{
	int nparam = 0;
	while (param[nparam++].type);
	if (!nparam) return NULL;

	CREATE2(DParam, p, nparam);

	int i;
	// NOTE that it's "i<=nparam", NOT "i<nparam".
	// It's for the D_TYPE_DONE
	for (i=0; i<=nparam; i++) {
		p[i].meta = &param[i];
		switch (p[i].meta->type) {
			case D_TYPE_DONE:
				break;
			case D_TYPE_FLOAT:
				p[i].f = p[i].meta->p1;
				break;
			case D_TYPE_VEC:
			case D_TYPE_COLOR:
				p[i].v[0] = p[i].meta->p1;
				p[i].v[1] = p[i].meta->p2;
				p[i].v[2] = p[i].meta->p3;
				break;
		}
	}

	return p;
}

