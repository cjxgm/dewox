
#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>


#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef PI
#define PI 3.1415927f
#endif

#ifndef LEN
#define LEN(A)	(sizeof(A)/sizeof((A)[0]))
#endif

#ifdef DEBUG
# define LOG_INFO(...)		fprintf(stderr, "::: "__VA_ARGS__);
# define LOG_ERROR(...)		fprintf(stderr, ">>> "__VA_ARGS__);
#else
# define LOG_INFO(...)
# define LOG_ERROR(...)
#endif

#endif

