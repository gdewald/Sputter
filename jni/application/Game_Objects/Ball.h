#pragma once

#include "zenilib.h"
//#include "..\Collision_object\Collision_object_2d.h"

class Ball /*: public Collision_circle*/ {
private:
	Zeni::Point2f position;
	float theta;
	float v;
	//Vector2f a_dir;
	//float a;
	float a_friction;
	enum BALL_STATE { MOVING, STOPPED, NOSTATE };
	enum BALL_MOD { POWER, FIRE, TRACTION, NOMOD };
	BALL_STATE state;
	BALL_MOD mod;
	int mod_num;

	Zeni::String texture;
	bool has_overlay;
	Zeni::String overlay;

	Zeni::Collision::Sphere col_sphere;

	const float max_speed;
	Ball();
public:
	Ball(Zeni::Point2f position_) : /*Collision_circle(position_, 64.0f),*/texture("ball_1"), mod(NOMOD), mod_num(0), has_overlay(false), position(position_), theta(0.0f), v(0.0f), a_friction(200.0f), state(STOPPED), max_speed(500.0f) { }

	bool is_stopped() { return state == STOPPED; }
	Zeni::Point2f get_position() { return position; }
	float get_radius() { return 32.0f; }
	float get_speed() { return v; }

	void set_friction(float val) { a_friction = val; }
	bool is_fireball() { return mod == FIRE; }
	void set_fireball() { mod = FIRE; mod_num = 1; }
	void set_powerball() { mod = POWER; mod_num = 1; }
	void set_spikeball() { mod = TRACTION; mod_num = 2; }

	//Collision stuff
	Zeni::Collision::Sphere get_col_sphere() { return Zeni::Collision::Sphere(Zeni::Point3f(position), 32.0f); }
	float move_from_col(Zeni::Collision::Sphere col_sphere, Zeni::Collision::Parallelepiped col_square);
	void reflect(float theta_wall, float dist);
	
	void update(const float time_step);
	void hit(float theta_, float power);
	void rotate(float theta_);
	void render();
};