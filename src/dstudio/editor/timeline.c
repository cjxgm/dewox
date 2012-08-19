
/************************************************************
 * dewox: timeline
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "editor_decl.h"
#include <stdio.h>

static void secondify_cb();
static void reset_cb();
static int  play_cb(int state);
static UIMenu menu[] = {
	{UI_MENU_BUTTON, &secondify_cb, "Secondify"},
	{UI_MENU_BUTTON, &reset_cb, "|<<"},
	{UI_MENU_TOGGLE, &play_cb, ">"},
	{UI_MENU_DONE}
};

static int start_time = 0;
static int end_time = 10*1000;	// 10 seconds

static int state = 0;
#define STATE_NONE				0
#define STATE_SELECT_TIME		1
#define STATE_SET_START_TIME	2
#define STATE_SET_END_TIME		3

static int orig_x;
static int orig_t;
static int orig_t2;

static void draw_time(int t, int w, int h);
static void set_playing_time(int t);

void editor_timeline_init()
{
	REGISTER_EDITOR("Timeline");
}

static void render(int w, int h)
{
	int t;
	if (d_playing) {
		// auto scroll to right
		t = lerp(d_playing_time-end_time, 0, end_time-start_time, 0, w);
		if (t > -30) {
			t = lerp(t+30, 0, w, 0, end_time-start_time);
			start_time += t;
			end_time += t;
		}

		// auto scroll to left
		t = lerp(d_playing_time-start_time, 0, end_time-start_time, 0, w);
		if (t < 0) {
			t = lerp(t, 0, w, 0, end_time-start_time);
			start_time += t;
			end_time += t;
		}
	}

	if (end_time < start_time+w) end_time = start_time + w;

	// background color
	glColor3f(0.4f, 0.4f, 0.4f);
	glRectf(0, 0, w, h);

	// blank out negative things
	t = lerp(0, start_time, end_time, 0, w);
	if (t > 0) {
		if (t > w) t = w;
		glColor3f(0.1f, 0.1f, 0.1f);
		glRectf(0, 0, t, h);
	}

	glColor3f(0.2f, 0.2f, 0.2f);
	int s = start_time / 1000;
	int e = end_time / 1000;
	glBegin(GL_LINES);
	for (; s<=e; s++) {
		float x = lerp(s*1000, start_time, end_time, 0, w);
		glVertex2f(x, 0);
		glVertex2f(x, h);
	}
	glEnd();

	// draw animation time
	if (d_active_param) {
		DParam * p = d_active_param;
		while (p->meta->type) {
			if (p->af.enabled) {
				float tf;
				float tt;
				if (p->meta->type == D_TYPE_FLOAT) {
					tf = p->af.tf;
					tt = p->af.tt;
				}
				else {
					tf = p->av.tf;
					tt = p->av.tt;
				}

				float x;
				glLineWidth(2.0);
				glBegin(GL_LINES);
				glColor3f(1.0f, 0.6f, 0.2f);
				x = lerp(tf, start_time, end_time, 0, w);
				glVertex2f(x, 0);
				glVertex2f(x, h);

				glColor3f(1.0f, 0.2f, 0.6f);
				x = lerp(tt, start_time, end_time, 0, w);
				glVertex2f(x, 0);
				glVertex2f(x, h);
				glEnd();
			}
			p++;
		}
	}

	draw_time(d_playing_time, w, h);
}

static void hover(int x, int y, int w, int h)
{
}

static void click(int x, int y, int w, int h, int btn, int stt)
{
	if (btn == WM_BUTTON_LEFT && stt == WM_BUTTON_DOWN) {
		set_playing_time(lerp(x, 0, w, start_time, end_time));
		state = STATE_SELECT_TIME;
		wm_require_refresh();
		return;
	}

	if (btn == WM_BUTTON_RIGHT && stt == WM_BUTTON_DOWN) {
		orig_x = x;
		orig_t = end_time;
		state = STATE_SET_END_TIME;
		return;
	}

	if (btn == WM_BUTTON_MID && stt == WM_BUTTON_DOWN) {
		orig_x = x;
		orig_t = start_time;
		orig_t2 = end_time;
		state = STATE_SET_START_TIME;
		return;
	}

	if (stt == WM_BUTTON_UP) {
		state = STATE_NONE;
		return;
	}
}

static void drag(int x, int y, int w, int h)
{
	int t;
	switch (state) {
		case STATE_SELECT_TIME:
			set_playing_time(lerp(x, 0, w, start_time, end_time));
			wm_require_refresh();
			break;
		case STATE_SET_START_TIME:
			t = lerp(x-orig_x, 0, w, 0, orig_t2-orig_t);
			start_time = orig_t - t;
			end_time = orig_t2 - t;
			wm_require_refresh();
			break;
		case STATE_SET_END_TIME:
			end_time = orig_t - lerp(x-orig_x, 0, w, 0, 10000);
			wm_require_refresh();
			break;
	}
}

static void keypress(int key, int w, int h)
{
}

static void draw_time(int t, int w, int h)
{
	static char buf[32];
	float x = lerp(t, start_time, end_time, 0, w);

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x, 0);
	glVertex2f(x, h);
	glEnd();

	sprintf(buf, "%d", t/1000 - (t<0));
	int fw = font_width(buf);
	glRectf(x-fw-8, h-20, x, h);
	glColor3f(0.2f, 0.2f, 0.2f);
	font_render(buf, x-fw-2, h-20);

	int t2 = t%1000;
	if (t2<0) t2 += 1000;
	sprintf(buf, ".%d", t2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x, h-20, x+font_width(buf)+2, h);
	glColor3f(0.2f, 0.2f, 0.2f);
	font_render(buf, x-4, h-20);
}

////////////////////////////////////////
//
// callbacks
//

static void secondify_cb()
{
	set_playing_time(d_playing_time / 1000 * 1000);
	wm_require_refresh();
}

static void reset_cb()
{
	set_playing_time(0);
	wm_require_refresh();
}

static int play_cb(int state)
{
	if (state == -1) return d_playing;
	if (state) d_play(wm_ticks());
	else d_stop();
	return d_playing;
}

static void set_playing_time(int t)
{
	d_playing_time = t;
	d_time_changed = 2;
	if (d_playing) {
		// to reset the player's "tape header"
		d_stop();
		d_play(wm_ticks());
	}
}

