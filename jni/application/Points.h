#pragma once

#include <zenilib.h>

class Points {
	int pts;
	int par;

	int damaged_walls;
	int broken_walls;
	int hits;
	
	static Points* instance;
	Points() {
		reset(0);
	}

public:
	static Points& get_Points() {
		if (!instance) instance = new Points();
		return *instance;
	}

	void hit() { hits++; }
	void wall_damage() { damaged_walls++; }
	void wall_break() { broken_walls++; }

	void reset(int par_) {
		par = par_;
		pts = 0;
		broken_walls = 0;
		damaged_walls = 0;
		hits = 0;
	}

	void render(Zeni::Point2f ul, Zeni::Point2f lr) {
		Zeni::get_Fonts()["system_36_800x600"].render_text(Zeni::String(Zeni::itoa(hits) + Zeni::String("/") + Zeni::itoa(par)), Zeni::Vector3f(lr.x - 75.0f, ul.y, 0), Zeni::Vector3f(1, 0, 0), Zeni::Vector3f(0, 1, 0), Zeni::get_Colors()["white"]);
		Zeni::get_Fonts()["system_36_800x600"].render_text(Zeni::itoa(pts), Zeni::Vector3f(lr.x - 75.0f, ul.y + 20.0f, 0), Zeni::Vector3f(1, 0, 0), Zeni::Vector3f(0, 1, 0), Zeni::get_Colors()["white"]);
	}
};