
#ifndef __LOG__
#define __LOG__

#include <cstdio>
using namespace std;

#define LOG(...) do { \
	fprintf(log_file, __VA_ARGS__); \
	fflush(log_file); \
} while(0)

extern FILE * log_file;

#endif

