
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

	virtual void (*delete)(UI * ui);
	virtual void (*paint)(UI * ui);
};
#define ui_get(lst)		list_get(lst, UI *)

void ui_init(UI * ui, int x, int y, int w, int h);

#include "widget/label.h"
#include "widget/button.h"

#endif

