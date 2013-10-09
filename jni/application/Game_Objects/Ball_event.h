#pragma once

#include <zenilib.h>
#include "../Game_States/Scoreboard_State.h"
#include "Ball.h"

class Ball_event {
private:
	bool active;
	Zeni::Point2f pos;
	float radius;
	Zeni::String t_name;

public:
	Ball_event(Zeni::Point2f pos_, Zeni::String t_name_) : pos(pos_), t_name(t_name_), radius(32.0f) { }

	Zeni::Point2f get_position() { return pos; }
	float get_radius() { return radius; }

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

	virtual bool is_colliding(Ball* b) {
		return (Zeni::Vector2f(b->get_position() - get_position()).magnitude() <= (get_radius()));
	}

	virtual void perform_collision(Ball* b) {
		Zeni::get_Game().pop_state();
		Zeni::get_Game().push_state(new Scoreboard_State());
	}
};

class Fireball_event :public Ball_event {
private:

public:

	Fireball_event(Zeni::Point2f pos_) : Ball_event(pos_, "fire_up") { }

	virtual void perform_collision(Ball* b) {
		b->set_fireball();
	}
};

class Spikeball_event : public Ball_event {
private:

public:

	Spikeball_event(Zeni::Point2f pos_) : Ball_event(pos_, "spike_up") { }

	virtual void perform_collision(Ball* b) {
		b->set_spikeball();
	}
};

class Powerball_event : public Ball_event {
private:

public:

	Powerball_event(Zeni::Point2f pos_) : Ball_event(pos_, "pow_up") { }

	virtual void perform_collision(Ball* b) {
		b->set_powerball();
	}
};