#pragma once

#include "zenilib.h"

using namespace Zeni;
using namespace std;

class Ball {
private:
	Point2f position;
	float theta;
	float v;
	//Vector2f a_dir;
	//float a;
	float a_friction;
	enum BALL_STATE { MOVING, STOPPED, NONE };
	BALL_STATE state;

	const float max_speed = 200.0f;
	Ball();
public:
	Ball(Point2f position_) : position(position_), theta(0.0f), v(0.0f), a_friction(30.0f), state(STOPPED) { }
	bool is_stopped() { return state == STOPPED; }
	Point2f get_position() { return position; }
	void update(const float time_step);
	void hit(float theta_, float power);
	void rotate(float theta_);
	void render();
};