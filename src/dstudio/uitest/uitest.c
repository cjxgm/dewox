
#include <GL/gl.h>

#include "uitest.h"
#include "font.h"
#include "event.h"
#include "common.h"
#include "widget/widgets.h"




static WButton btns[] = {
	{"Button Test"},
	{"Msgbox Without ActFunc"},
	{"Msgbox With ActFunc"},
};

static WRadioItem radio_items[] = {
	"Ha!", "Default", "Hoo!^_^", "Hello, world!",
	"One more!", "And this one", "Still...", NULL
};
static WRadio radio = {1, .items = radio_items};




void uitest_click(int button, int state, int x, int y)
{
	int i;
	for (i=0; i<LEN(btns); i++)
		wbutton_click(&btns[i], button, state, x, y);
	wradio_click(&radio, button, state, x, y);
}

void uitest_drag(int x, int y)
{
}

void uitest_hover(int x, int y)
{
	int i;
	for (i=0; i<LEN(btns); i++)
		wbutton_hover(&btns[i], x, y);
	wradio_hover(&radio, x, y);
}

void uitest_key(unsigned char k)
{
}

static void act_btn2(void * w)
{
	msgbox(w, NULL, "You comfirmed!", "You see, yet another one.");
}

void uitest_draw(int w, int h)
{
	draw_border(10, 10, w-20, h-10);

	float t = (w-36)/2.0f;
	int i;


	// border and title
	draw_border(18, 18, t-4, 70);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(20, 20, t-4, "Buttons", 0.0f);

	draw_border(18+t+4, 18, t-4, 70);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(20+t+4, 20, t-4, "Msgbox", 0.0f);

	draw_border(18, 96, w-36, 50);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(20, 98, w-40, "Radio", 0.0f);
	glColor3f(0.8f, 0.8f, 0.8f);
	draw_string(80, 98, w-100, radio_items[radio.selected], 0.0f);


	btns[0].x = 22;
	btns[0].y = 40;
	btns[0].w = t-12;
	btns[0].h = 20;

	btns[1].x = 22+t+4;
	btns[1].y = 40;
	btns[1].w = t-12;
	btns[1].h = 20;

	btns[2].x = 22+t+4;
	btns[2].y = 64;
	btns[2].w = t-12;
	btns[2].h = 20;

	for (i=0; i<LEN(btns); i++)
		wbutton_draw(&btns[i]);

	radio.x = 22;
	radio.y = 120;
	radio.w = w-44;
	radio.h = 20;
	wradio_draw(&radio);

	

	// button event proccess
	if (btns[1].clicked) {
		btns[1].clicked = 0;
		msgbox(&btns[1], NULL, "You clicked me!", "OK");
	}
	if (btns[2].clicked) {
		btns[2].clicked = 0;
		msgbox(&btns[2], (ActFunc)&act_btn2, "You clicked me!",
				"Another one will be popped up if you confirm this.");
	}
}

