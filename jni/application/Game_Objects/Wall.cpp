#include "Wall.h"

using namespace Zeni;
using namespace std;

void Wall::render() {
	render_image(texture_name, Point2f(position.x - texture_width / 2, position.y - texture_height / 2), Point2f(position.x + texture_width / 2, position.y + texture_height / 2), theta, 1.0f, position, false, Color());
}
