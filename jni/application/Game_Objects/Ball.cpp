#include "Ball.h"

using namespace Zeni;
using namespace std;

void Ball::update(const float time_step) {
	if (state == MOVING) {
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
	Video& vr = get_Video();
	render_image("ball_1", Point2f(position.x - 32.0f, position.y - 32.0f), Point2f(position.x + 32.0f, position.y + 32.0f), -theta, 1.0f, position, false, Color());
}