
#include "config.h"
#include "dutil.h"
#include "window.h"
#include "event.h"

int main()
{
	LOG_INFO("%s\n\n", VERSION_STRING);

	window_init();
	window_run();

	return 0;
}

