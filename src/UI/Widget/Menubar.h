
#ifndef __UI_MENUBAR__
#define __UI_MENUBAR__

#include "../UI.h"

typedef enum MenubarType
{
	MENUBAR_H,	// horizontal
	MENUBAR_V,	// vertical
}
MenubarType;

class Menubar : public UI
{
public:
	Menubar(int x, int y, int w, int h) :
		UI(x, y, w, h), menubarType(MENUBAR_H),
		widgets(new List<UI *>())
	{
		LOG("[Menubar] Created.");
	}
	Menubar(int x, int y, int w, int h, MenubarType mtype) :
		UI(x, y, w, h), menubarType(mtype),
		widgets(new List<UI *>())
	{
		LOG("[Menubar] Created.");
	}
	
	UIType getType() { return UI_TYPE_MENUBAR; }
	void paint();
	void resize(int w, int h);
	List<UI *> * add(UI * ui)
	{
		LOG("[Menubar] Add widget %d", ui->getType());
		return widgets->add(ui);
	}
private:
	MenubarType menubarType;
	List<UI *> * widgets;
};

#endif

