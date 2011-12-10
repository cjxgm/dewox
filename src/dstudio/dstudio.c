
#include <stdlib.h>
#include <GL/gl.h>

#include "event.h"
#include "common.h"
#include "font.h"
#include "config.h"
#include "widget/widgets.h"

// tabs
#include "info/info.h"
#include "scene/scene.h"
#include "track/track.h"
#include "pref/pref.h"
#include "uitest/uitest.h"




static WRadioItem tabs[] = {
	"Info", "Scene", "Track", "Preferences", "UI Test", NULL
};
//					 		  x  y  w  h   selected   items
static WRadio tab_switcher = {8, 0, 0, 20, 0,         tabs};




static void act_quit(void * w)
{
	exit(0);
}




void app_click(int button, int state, int x, int y)
{
	wradio_click(&tab_switcher, button, state, x, y);
	switch (tab_switcher.selected) {
	case 0: info_click  (button, state, x, y); break;
	case 1: scene_click (button, state, x, y); break;
	case 2: track_click (button, state, x, y); break;
	case 3: pref_click  (button, state, x, y); break;
	case 4: uitest_click(button, state, x, y); break;
	}
}

void app_drag(int x, int y)
{
	switch (tab_switcher.selected) {
	case 0: info_drag  (x, y); break;
	case 1: scene_drag (x, y); break;
	case 2: track_drag (x, y); break;
	case 3: pref_drag  (x, y); break;
	case 4: uitest_drag(x, y); break;
	}
}

void app_hover(int x, int y)
{
	wradio_hover(&tab_switcher, x, y);
	switch (tab_switcher.selected) {
	case 0: info_hover  (x, y); break;
	case 1: scene_hover (x, y); break;
	case 2: track_hover (x, y); break;
	case 3: pref_hover  (x, y); break;
	case 4: uitest_hover(x, y); break;
	}
}

void app_key(unsigned char k)
{
	if (k == '\e') {
		msgbox(&k, act_quit, "Quit?", "Quit Dewox");
		return;
	}
	switch (tab_switcher.selected) {
	case 0: info_key  (k); break;
	case 1: scene_key (k); break;
	case 2: track_key (k); break;
	case 3: pref_key  (k); break;
	case 4: uitest_key(k); break;
	}
}

void app_draw(int w, int h)
{
	tab_switcher.y = h - 28;
	tab_switcher.w = w - 16;
	wradio_draw(&tab_switcher);

	switch (tab_switcher.selected) {
	case 0: info_draw  (w, h-36); break;
	case 1: scene_draw (w, h-36); break;
	case 2: track_draw (w, h-36); break;
	case 3: pref_draw  (w, h-36); break;
	case 4: uitest_draw(w, h-36); break;
	}
}

