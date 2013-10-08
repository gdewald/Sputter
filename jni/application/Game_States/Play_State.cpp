#include "Play_State.h"
#include "../Points.h"
#include <list>

using namespace Zeni;
using namespace std;

Play_State::Play_State(String level_name) : m_time_passed(0.0f) {
	set_pausable(true);

	// Inititalize the private members
	ball = new Ball(Point2f(129.0f, 129.0f));
	controller = new Controller(ball);
	level = new Level(level_name);

	wall = new Wall(Point2f(100.0f, 100.0f), "hole_1", 20.0f, 40.0f, 1.15f);

	// Map the joystick buttons
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 4), 1);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_X /* x-axis */), 2);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_Y /* y-axis */), 3);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_X), 4);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_TRIGGER), 5);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 10), 6);

}

Play_State::Play_State() : m_time_passed(0.0f) {
	set_pausable(true);

	// Inititalize the private members
	ball = new Ball(Point2f(129.0f, 129.0f));
	controller = new Controller(ball);
	level = new Level();

	wall = new Wall(Point2f(100.0f, 100.0f), "hole_1", 20.0f, 40.0f, 1.15f);

	// Map the joystick buttons
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 4), 1);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_X /* x-axis */), 2);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_THUMB_Y /* y-axis */), 3);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_RIGHT_THUMB_X), 4);
	set_action(Zeni_Input_ID(SDL_JOYAXISMOTION, Joysticks::AXIS_LEFT_TRIGGER), 5);
	set_action(Zeni_Input_ID(SDL_JOYBUTTONDOWN, 10), 6);
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
	SDL_Delay(5);

	const float time_passed = m_chrono.seconds();
	const float time_step = time_passed - m_time_passed;
	m_time_passed = time_passed;

	//Only let the ball be controlled when it is stopped
	if (ball->is_stopped())
		controller->process_inputs();
	else {//Let the ball move
		ball->update(time_step);
		level->check_event_collisions(ball);
		level->check_tile_collisions(ball);
		level->check_terrain(ball);
	}
}

void Play_State::render() {
	Video& vr = get_Video();
	Colors& cr = get_Colors();

	Point2f camera_pos = ball->get_position();
	Window& window = get_Window();

	//Camera stops following ball on edges
	if (camera_pos.x < (window.get_width() / 2)) camera_pos.x = window.get_width() / 2;
	else if (camera_pos.x > level->get_width_px() - (window.get_width() / 2)) camera_pos.x = level->get_width_px() - (window.get_width() / 2);

	if (camera_pos.y < (window.get_height() / 2)) camera_pos.y = window.get_height() / 2;
	else if (camera_pos.y > level->get_height_px() - (window.get_height() / 2)) camera_pos.y = level->get_height_px() - (window.get_height() / 2);

	Point2f camera_ul = Point2f(camera_pos.x - (window.get_width() / 2), camera_pos.y - (window.get_height() / 2));
	Point2f camera_lr = Point2f(camera_pos.x + (window.get_width() / 2), camera_pos.y + (window.get_height() / 2));
	vr.set_2d(make_pair(camera_ul, camera_lr), true);

	level->render(camera_pos, get_Window().get_width(), get_Window().get_height());

	ball->render();
	if (ball->is_stopped())
		controller->render();

	Points::get_Points().render(camera_ul, camera_lr);

	//wall->render();

}
