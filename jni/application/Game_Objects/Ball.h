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
	enum BALL_STATE { MOVING, STOPPED, NONE };
	BALL_STATE state;

	//Collision_circle* col_obj

	const float max_speed;
	Ball();
public:
	Ball(Zeni::Point2f position_) : /*Collision_circle(position_, 64.0f),*/ position(position_), theta(0.0f), v(0.0f), a_friction(200.0f), state(STOPPED), max_speed(50.0f) { }

	bool is_stopped() { return state == STOPPED; }
	Zeni::Point2f get_position() { return position; }
	
	void update(const float time_step);
	void hit(float theta_, float power);
	void rotate(float theta_);
	void render();
};