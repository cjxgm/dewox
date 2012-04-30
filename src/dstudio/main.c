
/************************************************************
 * dewox: main.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "wm.h"

int main()
{
	wm_init();
	wm_require_refresh();
	wm_mainloop();
	return 0;
}

