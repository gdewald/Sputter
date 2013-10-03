#include "Ball.h"
#include <cassert>

using namespace Zeni;
using namespace std;

void Ball::update(const float time_step) {
	if (state == MOVING) {
		//Bounce off edges
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
	else if (state == COLLIDING) {

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

String potato = "potato";
String apple = "apple";

void Ball::render() {
	Video& vr = get_Video();
	Colors& cr = get_Colors();
	get_Fonts()["system_36_800x600"].render_text(apple, Vector3f(50.0f, 110.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	get_Fonts()["system_36_800x600"].render_text(potato, Vector3f(50.0f, 130.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);

	render_image("ball_1", Point2f(position.x - 32.0f, position.y - 32.0f), Point2f(position.x + 32.0f, position.y + 32.0f), -theta, 1.0f, position, false, Color());
}

float Ball::move_from_col(Collision::Sphere col_sphere, Collision::Parallelepiped col_square) {
	float dist = 0.0f;
	Collision::Sphere s = get_col_sphere();
	apple = ftoa(s.get_center().x) + " " + ftoa(s.get_center().y);

	if(s.intersects(col_square)) {
		float step = 0.001 * v;
		dist += step;
		position.x -= sin(theta) * step;
		position.y += cos(theta) * step;
		s = get_col_sphere();
	}

	return dist;
}

void Ball::reflect(float theta_wall, float dist) {
	if (theta_wall < 0.05f) theta = -theta; // Top
	else if (theta_wall < 1.575f) theta = -theta + 3.14f; //Right
	else if (theta_wall < 3.145f) theta = -theta; //Bottom
	else theta = -theta + 3.14f; //Left

	position.x += sin(theta) * dist;
	position.y -= cos(theta) * dist;
}
