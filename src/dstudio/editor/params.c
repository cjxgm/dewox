
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
static float drag_start_x = 0;
static float drag_start_value = 0;
static float drag_width = 0;




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
	drag_width = ww;
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
	if (stt == WM_BUTTON_DOWN && btn == WM_BUTTON_LEFT) {
		if (state == UI_BUTTON_STATE_ACTIVE) {
			state = UI_BUTTON_STATE_PRESSED;
			drag_start_x = x;
			// active_param->f <--> active_param->v[0];
			drag_start_value = active_param->v[state_btn];
			wm_require_refresh();
		}
	}

	if (stt == WM_BUTTON_UP && btn == WM_BUTTON_LEFT) {
		state = UI_BUTTON_STATE_NORMAL;
		hover(x, y, w, h);
		wm_require_refresh();
	}
}

static void drag(int x, int y, int w, int h)
{
	float s = 0;
	float t = 1;
	float p = 1e-3;

	if (active_param->meta->type == D_TYPE_FLOAT) {
		s = active_param->meta->p2;
		t = active_param->meta->p3;
		p = active_param->meta->p4;
		if (s == t) {
			s = 0;
			t = 1;
		}
		if (p == 0) {
			p = 1e-3;
		}
	}

	float v = lerp(x - drag_start_x, 0, drag_width, 0, t-s) +
			drag_start_value;
	v = ((int)(v / p)) * p;
	if (v < s) v = s;
	else if (v > t) v = t;
	// active_param->f <--> active_param->v[0];
	active_param->v[state_btn] = v;
	wm_require_refresh();
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

