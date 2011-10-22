
#include "App.h"
#include "Backend.h"

App * app;
Backend * backend;

int main()
{
	app = new App(0, 0, 0, 0);
	backend = new Backend();
	backend->run();
	return 0;
}
