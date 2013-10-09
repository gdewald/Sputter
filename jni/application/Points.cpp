#include "Points.h"
#include "Game_States\Level_Select_State.h"
#include <fstream>

using namespace Zeni;
using namespace std;

Points* Points::instance = nullptr;

void Points::reset(int par_) {
	par = par_;
	pts = 0;
	broken_walls = 0;
	damaged_walls = 0;
	hits = 0;

	in_hole = false;

	current_level = Level_Select_State::get_current_level();
	fstream scores_in(("levels\\" + current_level + ".score").c_str(), fstream::in);
	if (scores_in.good()) {
		scores_in >> high_score_hits >> high_score_pts;
	}
	else high_score_hits = 0;
	scores_in.close();
}

void Points::save_score() {
	if (high_score_hits == 0 || pts >= high_score_pts) {
		fstream scores_out(String("levels\\" + current_level + ".score").c_str(), fstream::out);
		scores_out << hits << " " << pts << endl;
		scores_out.close();
	}
}

void Points::render_scores() {
	Colors& cr = get_Colors();
	auto col = cr["white"];
	if (hits == par - 1) col = cr["yellow"];
	else if (hits > par) col = cr["red"];
	else if (hits == par) col = cr["green"];

	if (pts > high_score_pts) {
		get_Fonts()["system_36_800x600"].render_text("New High Score!", Vector3f(300.0f, 275.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), get_Colors()["white"]);
	}
	get_Fonts()["system_36_800x600"].render_text(String(itoa(hits) + String("/") + itoa(par)), Vector3f(300.0f, 300.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), col);
	get_Fonts()["system_36_800x600"].render_text(itoa(pts), Vector3f(300.0f, 325.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), get_Colors()["white"]);
	if (high_score_hits > 0) {
		get_Fonts()["system_36_800x600"].render_text("High Score:", Vector3f(300.0f, 350.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), get_Colors()["white"]);
		get_Fonts()["system_36_800x600"].render_text(String(itoa(high_score_hits) + String("/") + itoa(par)), Vector3f(300.0f, 375.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
		get_Fonts()["system_36_800x600"].render_text(itoa(high_score_pts), Vector3f(300.0f, 400.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), get_Colors()["white"]);
	}
}
