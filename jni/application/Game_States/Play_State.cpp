#include "Play_State.h"
#include "Game_Model.h"
#include <list>

using namespace Zeni;
using namespace std;

void Play_State::on_key(const SDL_KeyboardEvent& event) {
	//switch (event.keysym.sym) {
	//case SDLK_LEFT:
	//	Game_Model::get_instance().
	//}
}

void Play_State::on_push() {
	//get_Window().mouse_grab(true);
	get_Window().mouse_hide(false);
	//get_Game().joy_mouse.enabled = false;
}

void Play_State::on_pop() {
	//get_Window().mouse_grab(false);
	get_Window().mouse_hide(false);
	//get_Game().joy_mouse.enabled = true;
}

void Play_State::perform_logic() {
	Game_Model::get_instance().update();
}

void Play_State::render() {
	Video& vr = get_Video();
	Colors& cr = get_Colors();
	Game_Model& model = Game_Model::get_instance();
}