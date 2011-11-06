
#include <math.h>

#include "stacking.h"


#define MAP(V,SF,ST,DF,DT) \
	(((float)(V)-(float)(SF)) \
	/ ((float)(ST)-(float)(SF)) \
	* ((float)(DT)-(float)(DF)) \
	+ (float)(DF))

#ifndef PI
#define PI 3.14159f
#endif


float tri(float a)
{
	if (a<PI) return MAP(a, 0, PI, -1, 1);
	else return MAP(a, PI, 2*PI, 1, -1);
}

void opr_sine_render(oprinfo * oi)
{
	int i;
	int len = sizeof(oi->rendered)/sizeof(oi->rendered[0]);
	for (i=0; i<len; i++) {
		oi->rendered[i] = sin(oi->tick) * 32767;
		oi->tick += oi->step;
		if (oi->tick > 2*PI) oi->tick -= 2*PI;
	}
}

void opr_env_render(oprinfo * oi)
{
	if (!oi->inputs[0]) return;
	
	int i;
	int len = sizeof(oi->rendered)/sizeof(oi->rendered[0]);
	for (i=0; i<len; i++) {
		oi->rendered[i] = oi->inputs[0]->rendered[i]
				* MAP(oi->tick, 0, 2*PI, 1.0f, 0.0f);
		oi->tick += oi->step;
		if (oi->tick > 2*PI) oi->tick -= 2*PI;
	}
}

void opr_mix_render(oprinfo * oi)
{
	int incnt;
	for (incnt=0; oi->inputs[incnt] && incnt<4; incnt++);
	if (!incnt) return;
	
	int i, j, t;
	int len = sizeof(oi->rendered)/sizeof(oi->rendered[0]);
	for (i=0; i<len; i++) {
		t = 0;
		for (j=0; j<incnt; j++)
			t += oi->inputs[j]->rendered[i];
		oi->rendered[i] = t / incnt;
	}
}

void opr_tri_render(oprinfo * oi)
{
	int i;
	int len = sizeof(oi->rendered)/sizeof(oi->rendered[0]);
	for (i=0; i<len; i++) {
		oi->rendered[i] = tri(oi->tick) * 32767;
		oi->tick += oi->step;
		if (oi->tick > 2*PI) oi->tick -= 2*PI;
	}
}
