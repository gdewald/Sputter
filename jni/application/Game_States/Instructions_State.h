#pragma once
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Instructions_State : public Widget_Gamestate {
	Instructions_State(const Instructions_State &);
	Instructions_State operator=(const Instructions_State &) ;

public:
	Instructions_State()
		: Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
	{
	}

private:
	void on_key(const SDL_KeyboardEvent &event);
	void render();
};