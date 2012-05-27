
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

void ui_menu_draw(UIMenu menu[], UIMenuParam * param, int x, int y)
{
	int i, w;
	const char * s;
	for (i=0; menu[i].type; i++) {
		switch (menu[i].type) {
			case UI_MENU_FUNC:
				w = font_width(menu[i].label);
				if (i == param->active) {
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
				s = wm_get_editor(*(int*)menu[i].data)->name;
				w = font_width(s);
				draw_button(x+2, y+3, w+12, 25-6, (i == param->active));
				glColor3f(1.0f, 1.0f, 1.0f);
				glPointSize(1.0f);
				font_render(s, x+6, y+3);
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
				w = font_width(menu[i].label);
				if (mx > x+2 && mx < x+w+12) {
					if (param->active != i) {
						param->active = i;
						wm_require_refresh();
					}
					return;
				}
				x += w + 12;
				break;
			case UI_MENU_EDITOR_SELECTOR:
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

	if (param->active == -1) return;
	UIMenu * m = &menu[param->active];
	if (stt == WM_BUTTON_DOWN) {
		switch (m->type) {
			case UI_MENU_FUNC:
				if (btn == WM_BUTTON_LEFT)
					if (m->data) ((void (*)())m->data)();
				break;
			case UI_MENU_EDITOR_SELECTOR:
				/*
				if (btn == WM_BUTTON_LEFT)
					*(int *)m->data = (*(int *)m->data-3 + 1) %
							(wm_editor_cnt-3) + 3;
				else if (btn == WM_BUTTON_RIGHT)
					*(int *)m->data = (*(int *)m->data-3 - 1 +
							wm_editor_cnt-3) % (wm_editor_cnt-3) + 3;
				*/
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

	for (i=3; i<wm_editor_cnt; i++) {
		int x = editor_selector_x + 6;
		int y = editor_selector_y + 2 + (i-3)*20;

		if (i == editor_selected)
			draw_box_up(editor_selector_x, y,
						editor_selector_w, 20,
						0.2f, 0.5f, 1.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glPointSize(1.0f);
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

