#include "Controller.h"
#include <cmath>
#include <cstdlib>

using namespace Zeni;
using namespace std;

void Controller::process_inputs() {
	spread = 3.14f / 16 + (ltr + 1.0f)*3.14f / 8;
	range_mult = ltr + 1.0f;
	range_base = 5.0f + (rtr + 1.0f)*100.0f / 2;
	theta = -(atan2f(x, y) - 3.14f);
}

void Controller::fire() {
	int delta_theta = rand() % int(spread * 2.0f) - int(spread);
	float final_theta = theta + delta_theta;
	ball->hit(final_theta, range_base/105.0f);
}

void Controller::render() {
	process_inputs();

	Video& vr = get_Video();
	Colors& cr = get_Colors();
	get_Fonts()["system_36_800x600"].render_text("(" + ftoa(x, 3) + ", " + ftoa(y, 3) + ")", Vector3f(50.0f, 50.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	get_Fonts()["system_36_800x600"].render_text(ftoa(theta, 3) + " radians", Vector3f(50.0f, 70.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);

	Point2f center = ball->get_position();
	Vertex2f_Color start(Point2f(center.x, center.y), cr["yellow"]);
	Vertex2f_Color end1(Point2f(center.x + sin(theta - spread)*range_base*range_mult, center.y - cos(theta - spread)*range_base*range_mult), cr["green"]);
	Vertex2f_Color end2(Point2f(center.x + sin(theta + spread)*range_base*range_mult, center.y - cos(theta + spread)*range_base*range_mult), cr["green"]);

	vr.render(Line_Segment<Vertex2f_Color>(start, end1));
	vr.render(Line_Segment<Vertex2f_Color>(start, end2));
}