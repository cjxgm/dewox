
#ifndef __EVENT_MANAGER__
#define __EVENT_MANAGER__

#include "UI.h"

class EventManager
{
public:
	UI * mouseHooker;
	UI * keyHooker;

	EventManager():
		mouseListeners(new List<UI *>()),
		keyListeners(new List<UI *>())
	{}

	void mouseEvent(MouseEventType t, MouseButtonType b, int x, int y)
	{
		if (mouseHooker)
			mouseHooker->mouseEvent(t, b, x, y);

		else {
			mouseListeners->iterBegin();
			while (!mouseListeners->iterDone())
				mouseListeners->iterGet()->mouseEvent(t, b, x, y);
		}
	}
	void keyEvent(KeyEventType t, int keycode, int modifier)
	{
		if (keyHooker)
			keyHooker->keyEvent(t, keycode, modifier);

		else {
			keyListeners->iterBegin();
			while (!keyListeners->iterDone())
				keyListeners->iterGet()->keyEvent(t, keycode, modifier);
		}
	}

	List<UI *> * listenMouse(UI * ui) { return mouseListeners->add(ui); }
	List<UI *> * listenKey  (UI * ui) { return keyListeners->add(ui);   }

	void unlistenMouse(UI * ui) { mouseListeners->remove(ui); }
	void unlistenKey  (UI * ui) { keyListeners->remove(ui);   }
private:
	List<UI *> * mouseListeners;
	List<UI *> * keyListeners;
};

extern EventManager eventManager;

#endif

