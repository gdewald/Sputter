#include "Ball.h"

using namespace Zeni;
using namespace std;

void Ball::update() {
	if (state == MOVING) {
		position.x += sin(theta) * v;
		position.y -= cos(theta) * v;
		v -= a_friction;
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

void Ball::render() {
	Video& vr = get_Video();
	render_image("ball_1", Point2f(position.x - 32.0f, position.y - 32.0f), Point2f(position.x + 32.0f, position.y + 32.0f), 0.0f, 1.0f, Point2f(), false, Color());
}