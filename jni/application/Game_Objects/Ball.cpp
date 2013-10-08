#include "Ball.h"
#include "Points.h"
#include <cassert>

using namespace Zeni;
using namespace std;

bool wait = false;

void Ball::update(const float time_step) {
	if (state == MOVING) {
		float alpha;
		
		position.x += sin(theta) * v * time_step;
		position.y -= cos(theta) * v * time_step;
		v -= a_friction * time_step;

		static bool rev = false;

		if (!wait && texture != "ball_1") {
			if (rev) {
				texture = "ball_1";
				rev = false;
			}
			else if (texture.at(texture.size() - 1) == '1') {
				if (v > 100.0f)
					texture[texture.size() - 1] = '2';
				else rev = true;
			}
			else {
				texture[texture.size() - 1] = '1';
				rev = true;
			}
		}
		wait = false;


		if (v <= 0) {
			state = STOPPED;
			v = 0;
		}
		else if (v < 50) v *= .8f * time_step;
	}
}

void Ball::hit(float theta_, float power) {
	state = MOVING;
	theta = theta_;
	v = max_speed*power;
	if (mod == POWER)
		v *= 2.0f;
	Points::get_Points().hit();
}

void Ball::rotate(float theta_) {
	theta = theta_;
}

void Ball::render() {
	Video& vr = get_Video();
	Colors& cr = get_Colors();
	//get_Fonts()["system_36_800x600"].render_text(apple, Vector3f(50.0f, 110.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	//get_Fonts()["system_36_800x600"].render_text(potato, Vector3f(50.0f, 130.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	render_image(texture, Point2f(position.x - 32.0f, position.y - 32.0f), Point2f(position.x + 32.0f, position.y + 32.0f), 0.0f, 1.0f, position, false, Color());
	if (has_overlay) render_image(overlay, Point2f(position.x - 37.0f, position.y - 37.0f), Point2f(position.x + 90.0f, position.y + 90.0f), 0.0f, 1.0f, position, false, Color());
}

float Ball::move_from_col(Collision::Sphere col_sphere, Collision::Parallelepiped col_square) {
	float dist = 0.0f;
	Collision::Sphere s = get_col_sphere();

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
	if (theta_wall < 0.05f){
		texture = "ball_l1";
		theta = -theta; // Top
	}
	else if (theta_wall < 1.575f) {
		texture = "ball_u1";
		theta = -theta + 3.14f; //Right
	}
	else if (theta_wall < 3.145f) {
		texture = "ball_r1";
		theta = -theta; //Bottom
	}
	else {
		texture = "ball_u1";
		theta = -theta + 3.14f; //Left
	}
	wait = true;

	position.x += sin(theta) * dist;
	position.y -= cos(theta) * dist;

	//Bounce
	v *= .8f;
}
