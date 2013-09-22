#pragma once
#include <zenilib.h>
#include "../Controller.h"

using namespace std;
using namespace Zeni;

class Play_State : public Gamestate_II {
private:
	Ball* ball;
	Controller* controller;

public:
	Play_State();
	void on_event(const Zeni_Input_ID&, const float& confidence, const int& action);
	void on_push();
	void on_pop();
	void on_cover();
	void on_uncover();
	void perform_logic();
	void render();
};
