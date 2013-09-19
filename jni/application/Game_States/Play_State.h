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
	void on_push();
	void on_pop();
	void render();
};