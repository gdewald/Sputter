#include "Play_State.h"
#include <list>

using namespace Zeni;
using namespace std;

Play_State::Play_State() : m_time_passed(0.0f) {
	set_pausable(true);

	// Inititalize the private members
	ball = new Ball(Point2f(45.0f, 45.0f));
	controller = new Controller(ball);
	level = new Level();

	// Map the joystick buttons
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 7), 1);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_X /* x-axis */), 2);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_Y /* y-axis */), 3);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_X), 4);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_TRIGGER), 5);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 1), 6);
}

void Play_State::on_push() {
	get_Game().joy_mouse.enabled = false;
	get_Window().mouse_hide(true);
	m_chrono.start();
}

void Play_State::on_pop() {
	get_Game().joy_mouse.enabled = true;
	get_Window().mouse_hide(false);
	m_chrono.stop();
}
void Play_State::on_cover() {
	get_Game().joy_mouse.enabled = true;
	get_Window().mouse_hide(false);
}

void Play_State::on_uncover() {
	get_Game().joy_mouse.enabled = false;
	get_Window().mouse_hide(true);
}

void Play_State::on_event(const Zeni_Input_ID &, const float &confidence, const int &action) {
	switch (action) {
	case 1:
		if (confidence == 1.0f) {
			Game &game = get_Game();
			game.push_state(new Popup_Menu_State);
		}
		break;

	case 2:
		controller->set_x(confidence);
		break;

	case 3:
		controller->set_y(confidence);
		break;

	case 4:
		//spread = 3.14f / 16 + (confidence + 1.0f)*3.14f / 8;
		//range_mult = confidence + 1.0f;
		controller->set_ltr(confidence);
		break;

	case 5:
		//range_base = 5.0f + (confidence + 1.0f)*100.0f / 2;
		controller->set_rtr(confidence);
		break;

	case 6:
		controller->fire();
		break;

	default:
		break;
	}
}

void Play_State::perform_logic() {
	const float time_passed = m_chrono.seconds();
	const float time_step = time_passed - m_time_passed;
	m_time_passed = time_passed;

	SDL_Delay(5);
	if (!ball->is_stopped())
		ball->update(time_step);
}

void Play_State::render() {
	Video& vr = get_Video();
	Colors& cr = get_Colors();
	level->render(Point2f(), get_Window().get_width(), get_Window().get_height());

	ball->render();
	if (ball->is_stopped())
		controller->render();

	//vr.set_2d(make_pair(ball->get_position(), Point2f(640.0f, 480.0f)), true);
}
