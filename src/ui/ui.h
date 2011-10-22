
#ifndef __UI__
#define __UI__

#include "../util/util.h"
#include <assert.h>
#include <GL/gl.h>

enum ui_type {
	UI_TYPE_UNKNOWN,
	UI_TYPE_LABEL,
	UI_TYPE_BUTTON,
};

typedef struct ui UI;
typedef struct ui_label UI_LABEL;
typedef struct ui_button UI_BUTTON;

#define virtual
struct ui
{
	enum ui_type type;
	int x, y, w, h;
	char hidden;

	virtual void (*delete)(UI * ui);
	virtual void (*paint)(UI * ui);

	virtual void (*resize)(UI * ui, int w, int h);
	virtual void (*move  )(UI * ui, int x, int y);
};
#define ui_get(lst)		list_get(lst, UI *)

void ui_init(UI * ui, int x, int y, int w, int h);

#include "widget/label.h"
#include "widget/button.h"

#endif

