#pragma once
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Play_State : public Gamestate_Base {
	Play_State(const Play_State &);
	Play_State operator=(const Play_State &) ;

public:
	Play_State() {
		set_pausable(true);
	}

private:
	void on_push() {
		//get_Window().mouse_grab(true);
		get_Window().mouse_hide(true);
		//get_Game().joy_mouse.enabled = false;
	}

	void on_pop() {
		//get_Window().mouse_grab(false);
		get_Window().mouse_hide(false);
		//get_Game().joy_mouse.enabled = true;
	}
};