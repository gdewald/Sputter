#include "Ball_event.h"

using namespace Zeni;
using namespace std;

void Ball_event::render() {
	Video& vr = get_Video();
	Vertex2f_Texture v1 = Vertex2f_Texture(ul, Point2f());
	Vertex2f_Texture v2 = Vertex2f_Texture(Point2f(lr.x, ul.y), Point2f(1.0f, 0.0f));
	Vertex2f_Texture v3 = Vertex2f_Texture(lr, Point2f(1.0f, 1.0f));
	Vertex2f_Texture v4 = Vertex2f_Texture(Point2f(ul.x, lr.y), Point2f(0.0f, 1.0f));

	Quadrilateral<Vertex2f_Texture> quad = Quadrilateral<Vertex2f_Texture>(v1, v2, v3, v4);
	Material mat = Material(t_name);
	quad.fax_Material(&mat);

	vr.render(quad);
}