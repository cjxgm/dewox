
#include "../dui/config.h"
#include "../dutil/dutil.h"
#include "../dui/window.h"
#include "../dui/event.h"

int main()
{
	LOG_INFO("%s\n\n", VERSION_STRING);

	window_init();
	window_run();

	return 0;
}

