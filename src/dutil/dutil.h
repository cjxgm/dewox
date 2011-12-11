
#ifndef __DUTIL__
#define __DUTIL__

#include <stdio.h>
#include <math.h>


#ifndef NULL
# define NULL ((void *)0)
#endif

#ifndef PI
# define PI 3.1415927f
#endif

#ifndef LEN
# define LEN(A)	(sizeof(A)/sizeof((A)[0]))
#endif

#ifndef STEP
# define STEP(V,S)	(floor((V)/(S))*(S))
#endif

#ifndef CLAMP
# define CLAMP(V,MIN,MAX)	((V)<(MIN) ? (MIN) : ((V)>(MAX) ? (MAX) : (V)))
#endif

// map value ranged [sf, st] to [df, dt] linearly
float map(float value, float sf, float st, float df, float dt);


#ifdef DEBUG
# define LOG_INFO(...)		fprintf(stderr, "::: "__VA_ARGS__);
# define LOG_ERROR(...)		fprintf(stderr, ">>> "__VA_ARGS__);
#else
# define LOG_INFO(...)
# define LOG_ERROR(...)
#endif


#endif

