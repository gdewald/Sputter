#include "Test_State.h"
#include <zenilib.h>
#include <iostream>

using namespace Zeni;
using namespace std;

Test_State::Test_State() : x(0.0f), y(0.0f) {
	set_pausable(true);

	/*** Joyfun ***/

	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 7), 1);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_X /* x-axis */), 2);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_Y /* y-axis */), 3);
}

float Test_State::get_theta(float x, float y) {
	return 0.0f;
}

void Test_State::on_push() {
	get_Game().joy_mouse.enabled = false;
	get_Window().mouse_hide(true);
}

void Test_State::on_pop() {
	get_Game().joy_mouse.enabled = true;
	get_Window().mouse_hide(false);
}

void Test_State::on_event(const Zeni_Input_ID &, const float &confidence, const int &action) {
	float x, y;
	switch (action) {
	case 1:
		if (confidence == 1.0f) {
			Game &game = get_Game();
			game.push_state(new Popup_Menu_State);
		}
		break;

	case 2:
		x = confidence;
		cout << confidence;
		break;

	case 3:
		y = confidence;
		cout << confidence;
		break;

	default:
		break;
	}
}

void Test_State::perform_logic() {
	SDL_Delay(5);
	theta = get_theta(x, y);
}

void Test_State::render() {
	Colors& cr = get_Colors();
	get_Fonts()["system_36_800x600"].render_text(ftoa(x) + " " + ftoa(y), Vector3f(50.0f, 50.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
}
