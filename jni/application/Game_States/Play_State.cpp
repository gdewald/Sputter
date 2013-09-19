#include "Play_State.h"

using namespace Zeni;

void Play_State::on_push() {
	//get_Window().mouse_grab(true);
	get_Window().mouse_hide(false);
	//get_Game().joy_mouse.enabled = false;
}

void Play_State::on_pop() {
	//get_Window().mouse_grab(false);
	get_Window().mouse_hide(false);
	//get_Game().joy_mouse.enabled = true;
}

void Play_State::render() {
	Video& vr = get_Video();
	Colors& cr = get_Colors();

	Vertex2f_Color v1(Point2f(), cr["yellow"]);
	Vertex2f_Color v2(Point2f(100.0f, 0.0f), cr["blue"]);
	Vertex2f_Color v3(Point2f(100.0f, 100.0f), cr["blue"]);
	Vertex2f_Color v4(Point2f(0.0f, 100.0f), cr["yellow"]);

	Quadrilateral<Vertex2f_Color> q(v1, v2, v3, v4);

	vr.render(q);
}