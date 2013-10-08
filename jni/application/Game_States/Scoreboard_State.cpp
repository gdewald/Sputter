#include "Scoreboard_State.h"
#include "Level_Select_State.h"

using namespace Zeni;

void Next_level_button::on_accept() {
	get_Game().pop_state();
	Level_Select_State::push_next_level();
}

void Retry_button::on_accept() {
	get_Game().pop_state();
	Level_Select_State::push_current_level();
}

