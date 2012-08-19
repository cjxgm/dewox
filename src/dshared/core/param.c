
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
#include "../math/erp.h"
#include "../math/vector.h"

DParam * d_active_param;

DParam * d_create_param_from_meta(const DParamMeta * param)
{
	int nparam = 0;
	while (param[nparam++].type);
	if (!nparam) return NULL;

	CREATE2(DParam, p, nparam+1);	// +1 for D_TYPE_DONE

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

void d_apply_param_anim(DParam * param)
{
	if (!param) return;
	if (!d_time_changed) return;

	DParam * p = param;
	while (p->meta->type) {
		float prec = 1e-4;
		if (p->meta->type == D_TYPE_FLOAT) {
			if (p->meta->p4 != 0) prec = p->meta->p4;

			if (p->af.enabled) {
				if (d_playing_time <= p->af.tf)
					p->f = p->af.vf;
				else if (d_playing_time >= p->af.tt)
					p->f = p->af.vt;
				else p->f = lerp(d_playing_time, p->af.tf, p->af.tt,
						p->af.vf, p->af.vt);
				p->f = ((int)(p->f / prec)) * prec;	// clamp to precision
			}
		}
		p++;
	}
}

