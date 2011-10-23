
#include "App.h"
#include "Backend.h"
#include <cstdio>
#include <string>
using namespace std;

App * app;
Backend * backend;
FILE * log_file;
string dw_file;		// Dewox Workspace FILE

int main(int argc, char * argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Please specify a Dewox Workspace file.\n");
		return 1;
	}
	dw_file = argv[1];

	log_file = fopen("dewox.log", "w");
	if (!log_file) {
		fprintf(stderr, "Can not open log file.\n");
		return 1;
	}

	app = new App(0, 0, 0, 0);
	backend = new Backend();
	backend->run();

	fclose(log_file);

	return 0;
}
