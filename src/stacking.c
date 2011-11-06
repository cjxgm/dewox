
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stacking.h"


#ifndef NULL
#define NULL ((void *)0)
#endif


// in main.c
extern int win_w;
extern int win_h;

// in widget.c
int hovertest_box(int mx, int my, int x, int y, int w, int h);
void draw_cursor(int x, int y);
void draw_operator(int x, int y, int w, int type, int state, oprinfo * oi);
void draw_icon_sine(int x, int y);
void draw_icon_env(int x, int y);
void draw_icon_mix(int x, int y);
void draw_icon_tri(int x, int y);

// in menu.c
extern char is_menu;
void menu_open(void (*mdraw)(),
		void (*mclick)(int btn, int stt, int x, int y),
		void (*mhover)(int x, int y));
void menu_draw();
void menu_click(int btn, int stt, int x, int y);
void menu_hover(int x, int y);

// in prop.c
void prop_draw(oprinfo * oi);
void prop_click(int btn, int stt, int x, int y);
void prop_drag(int x, int y, oprinfo * oi);


static void menu_opr_draw();
static void menu_opr_click(int btn, int stt, int x, int y);
static void reconnect();
static int  check_error(int x, int y, int w);


#define OPRS_SIZE 100
opr oprs[OPRS_SIZE];
int oprcnt = 0;

static int cursor_x = 20;
static int cursor_y = 10;
static int left_down = 0;

static int selectcnt = 0;
static int dragging = 0;
static int dragging_mode = 0;	// 0: move    1: resize
static int dragging_x, dragging_y;


void click(int btn, int stt, int x, int y)
{
	if (is_menu) {
		menu_click(btn, stt, x, y);
		return;
	}

	if (x<200) {
		prop_click(btn, stt, x, y);
		if (!(btn == GLUT_LEFT && stt == GLUT_UP))
			return;
	}
	if (btn == GLUT_LEFT && stt == GLUT_DOWN) {
		left_down = 1;
		cursor_x = (x+5)/20;
		cursor_y = (y-5)/20;
		if (cursor_x < 10) cursor_x = 10;
		if (selectcnt) {
			dragging_x = cursor_x;
			dragging_y = cursor_y;
			dragging = 1;
		}
	}

	if (btn == GLUT_LEFT && stt == GLUT_UP) {
		prop_click(btn, stt, x, y);
		left_down = 0;
		if (dragging) {
			dragging = 0;

			int i;
			for (i=0; i<oprcnt; i++) {
				if (!oprs[i].selected) continue;
				int nx = cursor_x - dragging_x + oprs[i].x;
				int ny = cursor_y - dragging_y + oprs[i].y;
				int nw = cursor_x - dragging_x + oprs[i].w;
				if (nw<2) nw = 2;
				if (dragging_mode) {	// resize
					nx = oprs[i].x;
					ny = oprs[i].y;
				}
				else nw = oprs[i].w;
				if (nx<10) nx = 10;
				if (check_error(nx, ny, nw)) return;
			}

			for (i=0; i<oprcnt; i++) {
				if (!oprs[i].selected) continue;
				int nx = cursor_x - dragging_x + oprs[i].x;
				int ny = cursor_y - dragging_y + oprs[i].y;
				int nw = cursor_x - dragging_x + oprs[i].w;
				if (nw<2) nw = 2;
				if (dragging_mode) {	// resize
					nx = oprs[i].x;
					ny = oprs[i].y;
				}
				else nw = oprs[i].w;
				if (nx<10) nx = 10;
				oprs[i].x = nx;
				oprs[i].y = ny;
				oprs[i].w = nw;
			}

			reconnect();
		}
	}

	else if (btn == GLUT_LEFT+2 && stt == GLUT_DOWN) {
		int i;
		for (i=0; i<oprcnt; i++) {
			if (oprs[i].hovered) {
				selectcnt += (oprs[i].selected ? -1 : 1);
				oprs[i].selected = !oprs[i].selected;
			}
		}
	}
}

void drag(int x, int y)
{
	if (is_menu) return;

	if (left_down) {
		cursor_x = (x+5)/20;
		cursor_y = (y-5)/20;
		if (cursor_x < 10) cursor_x = 10;
	}

	if (selectcnt) {
		int i;
		for (i=0; i<oprcnt; i++)
			if (oprs[i].selected) break;
		prop_drag(x, y, &oprs[i].oi);
	}
}

void hover(int x, int y)
{
	if (is_menu) {
		menu_hover(x, y);
		return;
	}

	int i;
	for (i=0; i<oprcnt; i++) {
		oprs[i].hovered = hovertest_box(x, y,
				oprs[i].x*20, oprs[i].y*20, oprs[i].w*20-1, 20-1);
		if (oprs[i].hovered) dragging_mode = oprs[i].hovered  - 1;
	}
}

void draw()
{
	int i;
	for (i=0; i<oprcnt; i++) {
		// choose a state
		int state = 0;
		if (oprs[i].hovered) state = 1;
		if (oprs[i].selected) state = 4;

		draw_operator(oprs[i].x*20, oprs[i].y*20, oprs[i].w*20-1,
				oprs[i].type, state, &oprs[i].oi);
	}

	if (dragging)
		for (i=0; i<oprcnt; i++) {
			if (!oprs[i].selected) continue;
			int x = cursor_x - dragging_x + oprs[i].x;
			int y = cursor_y - dragging_y + oprs[i].y;
			int w = cursor_x - dragging_x + oprs[i].w;
			if (w<2) w = 2;
			if (dragging_mode) {	// resize
				x = oprs[i].x;
				y = oprs[i].y;
			}
			else w = oprs[i].w;
			if (x<10) x = 10;

			draw_operator(x*20, y*20, w*20-1,
					oprs[i].type, (check_error(x, y, w) ? 3 : 2), &oprs[i].oi);
		}

	if (selectcnt) {
		int i;
		for (i=0; i<oprcnt; i++)
			if (oprs[i].selected) break;
		prop_draw(&oprs[i].oi);
	}

	glLineWidth(1);
	glColor3f(0.5, 0.5, 1);
	glBegin(GL_LINES);
	glVertex2f(200, 0);
	glVertex2f(200, win_h);
	glEnd();

	draw_cursor(cursor_x*20, cursor_y*20);
	if (is_menu) menu_draw();
}

void keypress(int key, int x, int y)
{
	if (is_menu && key == 27) { // esc
		is_menu = 0;
		return;
	}

	if (key == ' ')
		menu_open(menu_opr_draw, menu_opr_click, NULL);

	else if (key == 27)		// esc
		exit(0);

	if (x<200) return;
	if (key == 'a') {// deselect all
		int i;

		if (selectcnt) {
			for (i=0; i<oprcnt; i++)
				oprs[i].selected = 0;
			selectcnt = 0;
		}
		else {
			for (i=0; i<oprcnt; i++)
				oprs[i].selected = 1;
			selectcnt = oprcnt;
		}
	}
}

void menu_opr_draw()
{
	glColor3f(0.3, 0.3, 0.3);
	int x = cursor_x*20+20;
	int y = cursor_y*20+20;
	glRectf(x, y, x+100, y+80);

	glColor3f(0.0, 1.0, 0.0);
	draw_icon_sine(x, y);
	draw_icon_env(x, y+20);
	draw_icon_mix(x, y+40);
	draw_icon_tri(x, y+60);
}

void menu_opr_click(int btn, int stt, int x, int y)
{
	int menux = cursor_x*20+20;
	int menuy = cursor_y*20+20;
	if (!hovertest_box(x, y, menux, menuy, 100, 80)) {
		is_menu = 0;
		return;
	}

	x -= cursor_x*20+20;
	y -= cursor_y*20+20;

	if (!check_error(cursor_x, cursor_y, 4)) {
		oprs[oprcnt].x = cursor_x;
		oprs[oprcnt].y = cursor_y;
		oprs[oprcnt].w = 4;
		oprs[oprcnt].hovered = 0;
		oprs[oprcnt].type = y / 20;
		oprs[oprcnt].selected = 0;

		oprinfo * oi = &oprs[oprcnt].oi;
		oi->step = 1.0f / ((rand()%50) + 5);
		oi->tick = 0;
		int i;
		for (i=0; i<sizeof(oi->rendered)/sizeof(oi->rendered[0]); i++)
			oi->rendered[i] = 0;
		for (i=0; i<4; i++)
			oi->inputs[i] = NULL;

		oprs[oprcnt++].enabled = 1;

		reconnect();
	}

	is_menu = 0;
}

void reconnect()
{
	int i, j, t;
	for (i=0; i<oprcnt; i++) {
		for (j=0; j<4; j++)
			oprs[i].oi.inputs[j] = NULL;
		t = 0;
		for (j=0; j<oprcnt; j++) {
			if (i==j) continue;
			if (oprs[i].y-oprs[j].y != 1) continue;
			if (t == 4) break;
			if (oprs[j].x+oprs[j].w<=oprs[i].x || oprs[j].x>=oprs[i].x+oprs[i].w)
				continue;
			oprs[i].oi.inputs[t++] = &oprs[j].oi;
		}

		if (t == 0) {
			oprinfo * oi = &oprs[i].oi;
			for (j=0; j<sizeof(oi->rendered)/sizeof(oi->rendered[0]); j++)
				oi->rendered[j] = 0;
		}
	}
}

int check_error(int x, int y, int w)
{
	int j;
	for (j=0; j<oprcnt; j++) {
		if (oprs[j].selected) continue;
		if (oprs[j].y != y) continue;
		if (oprs[j].x+oprs[j].w<=x || oprs[j].x>=x+w)
			continue;
		return 1;
	}
	return 0;
}

