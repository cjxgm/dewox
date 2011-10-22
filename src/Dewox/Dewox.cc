
#include "App.h"
#include "Backend.h"
#include <cstdio>
using namespace std;

App * app;
Backend * backend;
FILE * log_file;

int main()
{
	log_file = fopen("dewox.log", "w");
	if (!log_file) return 1;

	app = new App(0, 0, 0, 0);
	backend = new Backend();
	backend->run();

	fclose(log_file);

	return 0;
}
