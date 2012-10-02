
/************************************************************
 * dewox: menu.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "menu.h"
#include "ui.h"
#include "../wm.h"
#include "../../dshared/dshared.h"
#include <GL/gl.h>

static int * editor_type;
static int * editor_active;
static int editor_selected;
static int editor_selector_x;
static int editor_selector_y;
static int editor_selector_w;
static int editor_selector_h;
static void editor_selector_render(int w, int h);
static void editor_selector_click(int x, int y, int w, int h,
		int btn, int stt);
static void editor_selector_drag(int x, int y, int w, int h);

static int button_pressed = 0;
static void button_click(int x, int y, int w, int h, int btn, int stt);
static void toggle_click(int x, int y, int w, int h, int btn, int stt);

void ui_menu_draw(UIMenu menu[], UIMenuParam * param, int x, int y)
{
	int i, w;
	int o = 0;
	const char * s;
	for (i=0; menu[i].type; i++) {
		switch (menu[i].type) {
			case UI_MENU_FUNC:
				w = font_width(menu[i].label);
				if (i+o == param->active) {
					glColor3f(0.2f, 0.2f, 1.0f);
					glBegin(GL_QUADS);
					glVertex2f(x+2, y+3);
					glVertex2f(x+w+12, y+3);
					glVertex2f(x+w+12, y+25-3);
					glVertex2f(x+2, y+25-3);
					glEnd();
				}
				glColor3f(0.8f, 0.8f, 0.8f);
				glPointSize(1.0f);
				font_render(menu[i].label, x+6, y+3);
				x += w + 12;
				break;
			case UI_MENU_EDITOR_SELECTOR:
				if (!menu[i].data) break;
				s = wm_get_editor(*(int*)menu[i].data)->name;
				w = font_width(s);
				draw_button(x+2, y+3, w+12, 25-6, (i+o == param->active));
				glColor3f(1.0f, 1.0f, 1.0f);
				glPointSize(1.0f);
				font_render(s, x+6, y+3);
				x += w + 12;
				break;
			case UI_MENU_SUBMENU:
				if (!menu[i].data) break;
				menu = menu[i].data;
				o = i;
				i = -1;
				x += 10;
				break;
			case UI_MENU_BUTTON:
				w = font_width(menu[i].label);
				draw_button(x+2, y+3, w+10, y+19,
						(i+o == param->active ?
							(button_pressed ?
								UI_BUTTON_STATE_PRESSED :
								UI_BUTTON_STATE_ACTIVE) :
							UI_BUTTON_STATE_NORMAL));
				glColor3f(0.8f, 0.8f, 0.8f);
				glPointSize(1.0f);
				font_render(menu[i].label, x+6, y+3);
				x += w + 12;
				break;
			case UI_MENU_TOGGLE:
				w = font_width(menu[i].label);
				draw_button(x+2, y+3, w+10, y+19,
						(((int (*)(int))menu[i].data)(-1) ?
							UI_BUTTON_STATE_TOGGLED :
							(i+o == param->active ?
								UI_BUTTON_STATE_ACTIVE :
								UI_BUTTON_STATE_NORMAL)));
				glColor3f(0.8f, 0.8f, 0.8f);
				glPointSize(1.0f);
				font_render(menu[i].label, x+6, y+3);
				x += w + 12;
				break;
			default:
				break;
		}
	}
}

void ui_menu_hover(UIMenu menu[], UIMenuParam * param,
		int x, int y, int mx, int my)
{
	int i, w;
	int o = 0;
	for (i=0; menu[i].type; i++) {
		if (my <= y+3 || my >= y+25-3) {
			if (param->active != -1) {
				param->active = -1;
				wm_require_refresh();
			}
			continue;
		}

		switch (menu[i].type) {
			case UI_MENU_FUNC:
			case UI_MENU_BUTTON:
			case UI_MENU_TOGGLE:
				w = font_width(menu[i].label);
				if (mx > x+2 && mx < x+w+12) {
					if (param->active != i+o) {
						param->active = i+o;
						wm_require_refresh();
					}
					return;
				}
				x += w + 12;
				break;
			case UI_MENU_EDITOR_SELECTOR:
				if (!menu[i].data) break;
				editor_selector_x = wm_active_win_x() + x;
				w = font_width(wm_get_editor(*(int *)menu[i].data)->name);
				if (mx > x+2 && mx < x+w+12) {
					if (param->active != i) {
						param->active = i;
						wm_require_refresh();
					}
					return;
				}
				x += w + 12;
				break;
			case UI_MENU_SUBMENU:
				if (!menu[i].data) break;
				menu = menu[i].data;
				o = i;
				i = -1;
				x += 10;
				break;
			default:
				break;
		}
	}
	if (param->active) {
		param->active = -1;
		wm_require_refresh();
	}
}

void ui_menu_click(UIMenu menu[], UIMenuParam * param,
		int x, int y, int mx, int my, int btn, int stt)
{
	int i;
	int o = 0;

	if (param->active == -1) return;
	for (i=0; i<=param->active; i++) {
		if (menu[i-o].type == UI_MENU_SUBMENU) {
			menu = menu[i-o].data;
			o += i;
		}
	}
	UIMenu * m = &menu[i-o-1];
	if (stt == WM_BUTTON_DOWN) {
		switch (m->type) {
			case UI_MENU_FUNC:
				if (btn == WM_BUTTON_LEFT)
					if (m->data) ((void (*)())m->data)();
				break;
			case UI_MENU_EDITOR_SELECTOR:
				if (btn != WM_BUTTON_LEFT) break;
				editor_active = &param->active;
				editor_type = m->data;
				editor_selected = *editor_type;
				// 'editor_selector_x' is initialized in 'ui_menu_hover'
				// +12 for border blanks
				editor_selector_h = (wm_editor_cnt - 3) * 20 + 4;
				editor_selector_y = wm_active_win_y() -
									20 * (editor_selected - 3);
				editor_selector_w = 0;
				for (i=3; i<wm_editor_cnt; i++) {
					int w = font_width(wm_get_editor(i)->name);
					if (w > editor_selector_w)
						editor_selector_w = w;
				}
				editor_selector_w += 12;
				if (editor_selector_x + editor_selector_w > wm_win_w)
					editor_selector_x = wm_win_w - editor_selector_w;
				wm_capture(&editor_selected, editor_selector_render, NULL,
						editor_selector_click, editor_selector_drag, NULL);
				wm_require_refresh();
				break;
			case UI_MENU_BUTTON:
				if (btn != WM_BUTTON_LEFT) break;
				button_pressed = 1;
				wm_capture(m->data, NULL, NULL, button_click, NULL, NULL);
				wm_require_refresh();
				break;
			case UI_MENU_TOGGLE:
				if (btn != WM_BUTTON_LEFT) break;
				i = ((int (*)(int))m->data)(-1);
				((int (*)(int))m->data)(!i);
				wm_capture(&i, NULL, NULL, toggle_click, NULL, NULL);
				wm_require_refresh();
				break;
			default:
				break;
		}
	}
}

////////////////////////////////////////
//
// editor selector
//

static void editor_selector_render(int w, int h)
{
	int i;

	glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
	glRectf(editor_selector_x, editor_selector_y,
			editor_selector_x + editor_selector_w,
			editor_selector_y + editor_selector_h);

	glPointSize(1.0f);
	for (i=3; i<wm_editor_cnt; i++) {
		int x = editor_selector_x + 6;
		int y = editor_selector_y + 2 + (i-3)*20;

		if (i == editor_selected) {
			draw_box_up(editor_selector_x, y,
						editor_selector_w, 20,
						0.2f, 0.5f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		else glColor3f(0.8f, 0.8f, 0.8f);
		font_render(wm_get_editor(i)->name, x, y+2);
	}

	draw_outline(editor_selector_x, editor_selector_y,
				 editor_selector_w, editor_selector_h);
}

static void editor_selector_click(int x, int y, int w, int h,
		int btn, int stt)
{
	if (btn == WM_BUTTON_RIGHT) {
		*editor_active = -1;
		wm_uncapture();
		wm_require_refresh();
		return;
	}

	if (btn == WM_BUTTON_LEFT && stt == WM_BUTTON_UP) {
		*editor_active = -1;
		*editor_type = editor_selected;
		wm_uncapture();
		wm_require_refresh();
	}
}

static void editor_selector_drag(int x, int y, int w, int h)
{
	if (editor_selector_y < 0 && y < 10) {
		editor_selector_y += 4;
		wm_require_refresh();
	}

	if (editor_selector_y+editor_selector_h > wm_win_h &&
			y > wm_win_h-10) {
		editor_selector_y -= 4;
		wm_require_refresh();
	}

	int t = (y - editor_selector_y - 2) / 20 + 3;
	if (t < 3) t = 3;
	else if (t >= wm_editor_cnt) t = wm_editor_cnt - 1;
	if (t != editor_selected) {
		editor_selected = t;
		wm_require_refresh();
	}
}

////////////////////////////////////////
//
// other captures
//

static void button_click(int x, int y, int w, int h, int btn, int stt)
{
	if (stt == WM_BUTTON_UP) {
		if (wm_capdata()) {
			void * callback = wm_capdata();
			wm_uncapture();
			((void (*)())callback)();
		}
		else wm_uncapture();
		button_pressed = 0;
		wm_require_refresh();
	}
}

static void toggle_click(int x, int y, int w, int h, int btn, int stt)
{
	if (stt == WM_BUTTON_UP)
		wm_uncapture();
}
