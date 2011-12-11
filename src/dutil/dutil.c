
#include "dutil.h"

// map value ranged [sf, st] to [df, dt] linearly
float map(float value, float sf, float st, float df, float dt)
{
	return (value-sf) / (st-sf) * (dt-df) + df;
}

