#pragma once
#include <zenilib.h>
#include "../Controller.h"
#include "../Game_Map/Level.h"
#include "../Game_Objects/Wall.h"

class Play_State : public Zeni::Gamestate_II {
private:
	Ball* ball;
	Wall* wall;
	Controller* controller;
	Level* level;
	Zeni::Chronometer<Zeni::Time> m_chrono;
	float m_time_passed;

public:
	Play_State();
	Play_State(Zeni::String level_name);
	void on_event(const Zeni::Zeni_Input_ID& id, const float& confidence, const int& action);
	void on_push();
	void on_pop();
	void on_cover();
	void on_uncover();
	void perform_logic();
	void step(float m_timestep);
	void render();
};
