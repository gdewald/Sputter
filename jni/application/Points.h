#pragma once

#include <zenilib.h>
#include <map>

class Points {
	int pts;
	int par;
	int high_score_hits;
	int high_score_pts;

	int damaged_walls;
	int broken_walls;
	int hits;

	Zeni::String current_level;
	
	static Points* instance;
	Points() {
		reset(0);
	}

public:
	static Points& get_Points() {
		if (!instance) instance = new Points();
		return *instance;
	}

	void save_score();

	void hit() { hits++; }
	void wall_damage() { damaged_walls++; }
	void wall_break() { broken_walls++; }

	void reset(int par_);

	void render(Zeni::Point2f ul, Zeni::Point2f lr) {
		Zeni::Colors& cr = Zeni::get_Colors();
		Zeni::String col = "white";
		if (hits == par - 1) col = "yellow";
		else if (hits > par) col = "red";
		else if (hits == par) col = "green";

		Zeni::get_Fonts()["system_36_800x600"].render_text(Zeni::String(Zeni::itoa(hits) + Zeni::String("/") + Zeni::itoa(par)), Zeni::Vector3f(lr.x - 75.0f, ul.y, 0), Zeni::Vector3f(1, 0, 0), Zeni::Vector3f(0, 1, 0), cr[col]);
		Zeni::get_Fonts()["system_36_800x600"].render_text(Zeni::itoa(pts), Zeni::Vector3f(lr.x - 75.0f, ul.y + 20.0f, 0), Zeni::Vector3f(1, 0, 0), Zeni::Vector3f(0, 1, 0), Zeni::get_Colors()["white"]);
	}

	void render_scores();
};
