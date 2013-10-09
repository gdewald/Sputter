#include "Scoreboard_State.h"
#include "Level_Select_State.h"
#include "../Points.h"

using namespace Zeni;

void save_score() {
	Points::get_Points().save_score();
}

void Next_level_button::on_accept() {
	save_score();
	get_Game().pop_state();
	Level_Select_State::push_next_level();
}

void Retry_button::on_accept() {
	save_score();
	get_Game().pop_state();
	Level_Select_State::push_current_level();
}

void Scoreboard_State::render() {
	Widget_Gamestate::render();
	auto& p = Points::get_Points();
	p.render_scores();
}
