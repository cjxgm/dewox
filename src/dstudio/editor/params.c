
/************************************************************
 * dewox: props
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"
#include <stdio.h>

static DParam * config;
static DParamMeta config_meta[] = {
	{D_TYPE_FLOAT, "ranged", 0.2, 0.0, 1.0, 0.01},
	{D_TYPE_FLOAT, "inf", 0.2},
	{D_TYPE_VEC  , "vector", 0.5, 0.2, 1.0},
	{D_TYPE_COLOR, "color", 0.5, 0.8, 0.1},
	{D_TYPE_DONE}
};

static void config_cb();

static UIMenu menu[] = {
	{UI_MENU_BUTTON, &config_cb, "#"},
	{UI_MENU_DONE}
};

static DParam * active_param = NULL;
static int state = UI_BUTTON_STATE_NORMAL;
static int state_btn = 0;




void editor_params_init()
{
	REGISTER_EDITOR("Parameters");
	config = d_create_param_from_meta(config_meta);
}

static void render(int w, int h)
{
	glColor3f(0.1, 0.1, 0.1);
	glRectf(0, 0, w, h);

	if (!d_active_param) {
		glColor3f(1.0, 0.5, 0.2);
		font_render("No Parameters.", 10, h-30);
		return;
	}
	
	// calculate the label column's width
	DParam * p = d_active_param;
	float maxw = 0;
	while (p->meta->type) {
		float w = font_width(p->meta->name);
		if (w > maxw) maxw = w;
		p++;
	}
	maxw += 20;

	// draw the label and the value
	p = d_active_param;
	while (p->meta->type) {
		float y = h-10 - 20 - (p-d_active_param)*20;

		glColor3f(0.2, 0.8, 0.2);
		font_render(p->meta->name, 10, y);

		switch (p->meta->type) {
			case D_TYPE_FLOAT:
				draw_float_box(p, maxw, y, w-maxw-10, 18,
						(active_param == p ?
								state :
								UI_BUTTON_STATE_NORMAL));
				break;
			case D_TYPE_VEC:
				draw_vec_box(p, maxw, y, w-maxw-10, 18,
						(active_param == p ?
								state :
								UI_BUTTON_STATE_NORMAL), state_btn);
				break;
			case D_TYPE_COLOR:
				draw_color_box(p, maxw, y, w-maxw-10, 18,
						(active_param == p ?
								state :
								UI_BUTTON_STATE_NORMAL), state_btn);
				break;
			default:
				break;
		}
		p++;
	}
}

static void hover(int x, int y, int w, int h)
{
	if (!d_active_param) return;

	// calculate the label column's width
	DParam * p = d_active_param;
	float maxw = 0;
	while (p->meta->type) {
		float w = font_width(p->meta->name);
		if (w > maxw) maxw = w;
		p++;
	}
	maxw += 20;

	float ww = w-maxw-10;		// widget width
	if (ww <= 0) return;
	float wh = 18;				// widget height

	// process event
	p = d_active_param;
	while (p->meta->type) {
		float wy = h-10 - 20 - (p-d_active_param)*20;	// widget y
		int t;

		switch (p->meta->type) {
			case D_TYPE_FLOAT:
				if (x>maxw && x<maxw+ww && y>wy && y<wy+wh) {
					if (state != UI_BUTTON_STATE_ACTIVE ||
								active_param != p) {
						state = UI_BUTTON_STATE_ACTIVE;
						active_param = p;
						wm_require_refresh();
					}
					return;
				}
			case D_TYPE_VEC:
				if (x>maxw && x<maxw+ww && y>wy && y<wy+wh) {
					t = (x-maxw) * 3 / ww;
					if (state != UI_BUTTON_STATE_ACTIVE ||
								active_param != p ||
								state_btn != t) {
						state = UI_BUTTON_STATE_ACTIVE;
						active_param = p;
						state_btn = t;
						wm_require_refresh();
					}
					return;
				}
				break;
			case D_TYPE_COLOR:
				if (x>maxw && x<maxw+ww && y>wy && y<wy+wh) {
					if (x-maxw > ww-18) t = 3;
					else t = (x-maxw) * 3 / (ww-20);

					if (state != UI_BUTTON_STATE_ACTIVE ||
								active_param != p ||
								state_btn != t) {
						state = UI_BUTTON_STATE_ACTIVE;
						active_param = p;
						state_btn = t;
						wm_require_refresh();
					}
					return;
				}
				break;
			default:
				break;
		}
		p++;
	}

	if (state != UI_BUTTON_STATE_NORMAL || active_param) {
		active_param = NULL;
		state = UI_BUTTON_STATE_NORMAL;
		state_btn = 0;
		wm_require_refresh();
	}
}

static void click(int x, int y, int w, int h, int btn, int stt)
{
}

static void drag(int x, int y, int w, int h)
{
}

static void keypress(int key, int w, int h)
{
}

////////////////////////////////////////
//
// callbacks
//

static void config_cb()
{
	d_active_param = config;
}

