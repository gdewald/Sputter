#include "Test_State.h"
#include <zenilib.h>
#include <iostream>
#include <cmath>

using namespace Zeni;
using namespace std;

Test_State::Test_State() : x(0.0f), y(0.0f), theta(0.0f), range_base(50.0f), spread(3.14f/8) {
	set_pausable(true);

	/*** Joyfun ***/

	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 7), 1);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_X /* x-axis */), 2);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_Y /* y-axis */), 3);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_X), 4);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_TRIGGER), 5);
}

float Test_State::get_theta(float x, float y) {
	return -(atan2f(x, y) - 3.14f);
}

void Test_State::on_push() {
	get_Game().joy_mouse.enabled = false;
	get_Window().mouse_hide(true);
}

void Test_State::on_pop() {
	get_Game().joy_mouse.enabled = true;
	get_Window().mouse_hide(false);
}
void Test_State::on_cover() {
	get_Game().joy_mouse.enabled = true;
	get_Window().mouse_hide(false);
}

void Test_State::on_uncover() {
	get_Game().joy_mouse.enabled = false;
	get_Window().mouse_hide(true);
}

void Test_State::on_event(const Zeni_Input_ID &, const float &confidence, const int &action) {
	switch (action) {
	case 1:
		if (confidence == 1.0f) {
			Game &game = get_Game();
			game.push_state(new Popup_Menu_State);
		}
		break;

	case 2:
		x = confidence;
		break;

	case 3:
		y = confidence;
		break;

	case 4:
		spread = 3.14f / 16 + (confidence + 1.0f)*3.14f / 8;
		range_mult = confidence + 1.0f;
		ltc = confidence;
		break;

	case 5:
		range_base = 5.0f + (confidence + 1.0f)*100.0f / 2;
		rtc = confidence;
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
	Video& vr = get_Video();
	Colors& cr = get_Colors();
	get_Fonts()["system_36_800x600"].render_text("(" + ftoa(x, 3) + ", " + ftoa(y, 3) + ")", Vector3f(50.0f, 50.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	get_Fonts()["system_36_800x600"].render_text(ftoa(theta, 3) + " radians", Vector3f(50.0f, 70.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	get_Fonts()["system_36_800x600"].render_text(ftoa(ltc, 5) + " LTC", Vector3f(50.0f, 90.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	get_Fonts()["system_36_800x600"].render_text(ftoa(rtc, 5) + " RTC", Vector3f(50.0f, 110.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);

	float center_x = get_Window().get_height() / 2.0f;
	float center_y = get_Window().get_height() / 2.0f;
	Vertex2f_Color center(Point2f(center_x, center_y), cr["yellow"]);
	Vertex2f_Color end1(Point2f(center_x + sin(theta - spread)*range_base*range_mult, center_y - cos(theta - spread)*range_base*range_mult), cr["yellow"]);
	Vertex2f_Color end2(Point2f(center_x + sin(theta + spread)*range_base*range_mult, center_y - cos(theta + spread)*range_base*range_mult), cr["yellow"]);

	vr.render(Line_Segment<Vertex2f_Color>(center, end1));
	vr.render(Line_Segment<Vertex2f_Color>(center, end2));
}
