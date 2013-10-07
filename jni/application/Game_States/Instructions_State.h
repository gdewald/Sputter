#pragma once
#include <zenilib.h>
//#include "Play_State.h"

class Instructions_State : public Zeni::Widget_Gamestate {
	Instructions_State(const Instructions_State &);
	Instructions_State operator=(const Instructions_State &);

public:
	Instructions_State()
		: Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f))) {
	}

private:
	void on_key(const SDL_KeyboardEvent &event);
	void render();
};