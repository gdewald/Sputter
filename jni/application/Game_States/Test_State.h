#pragma once
#include <zenilib.h>

using namespace Zeni;
using namespace std;

class Test_State : public Gamestate_II {
private:
	float x, y;
	float theta;
	float range_base;
	float range_mult;
	float spread;
	float ltc;
	float rtc;

public:
	Test_State();
	void on_event(const Zeni_Input_ID&, const float& confidence, const int& action);
	void on_push();
	void on_pop();
	void on_cover();
	void on_uncover();
	void perform_logic();
	void render();
	float get_theta(float x, float y);
};
