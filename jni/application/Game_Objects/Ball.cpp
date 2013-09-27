#include "Ball.h"

using namespace Zeni;
using namespace std;

void Ball::update(const float time_step) {
	if (state == MOVING) {
		//Teleport ball like in pacman - super fake
		float alpha;
		if (position.x > 30 * 64.0f - 32.0f) theta = -theta;
		else if (position.x < 32.0f) theta = -theta;
		else if (position.y > 30 * 64.0f - 32.0f) theta = -theta + 3.14f;
		else if (position.y < 32.0f) theta = -theta + 3.14f;
		
		position.x += sin(theta) * v * time_step;
		position.y -= cos(theta) * v * time_step;
		v -= a_friction * time_step;
		if (v <= 0) {
			state = STOPPED;
			v = 0;
		}
	}
}

void Ball::hit(float theta_, float power) {
	state = MOVING;
	theta = theta_;
	v = max_speed*power;
}

void Ball::rotate(float theta_) {
	theta = theta_;
}

void Ball::render() {
	//Video& vr = get_Video();
	//Colors& cr = get_Colors();
	//get_Fonts()["system_36_800x600"].render_text(ftoa(theta, 5) + " ball_theta", Vector3f(position.x - 100.0f, position.y - 100.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);

	render_image("ball_1", Point2f(position.x - 32.0f, position.y - 32.0f), Point2f(position.x + 32.0f, position.y + 32.0f), -theta, 1.0f, position, false, Color());
}