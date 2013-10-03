#pragma once

#include <zenilib.h>
#include "Ball.h"

class Ball_event {
private:
	bool active;
	Zeni::Point2f pos;
	float radius;
	Zeni::String t_name;

public:
	Ball_event(Zeni::Point2f pos_, Zeni::String t_name_) : pos(pos_), t_name(t_name_) { }

	Zeni::Point2f get_position() { return pos; }

	virtual bool is_colliding(Ball* b) {
		return (Zeni::Vector2f(b->get_position() - pos).magnitude() <= (b->get_radius() + radius));
	}
	virtual void perform_collision(Ball* b) = 0;

	virtual void render();
};

class Hole_event : public Ball_event {
private:

public:

	Hole_event(Zeni::Point2f pos_) : Ball_event(pos_, "hole_1") { }

	virtual void perform_collision(Ball* b) {
		Zeni::get_Game().pop_state();
	}
};
