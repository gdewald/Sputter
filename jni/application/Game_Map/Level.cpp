#include "Level.h"
#include "Tile.h"

using namespace Zeni;
using namespace std;

const float Level_position::tile_dim = 64.0f;

Level::Level() {
	for (int i = 0; i < 100; i++) {
		map[Level_position(0, 0)] = Tile(GRASS_1);
	}
	map[Level_position(4, 4)] = Tile(HOLE_1);
}

void Level::render(Zeni::Point2f pos, float screen_width, float screen_height) {
	for (Level_position p(1, 1); p.location.first < 5; p.location.first++) {
		for (p.location.second = 1; p.location.second < 5; p.location.second++) {
			map[p].render(Point2f(p.location.first*p.tile_dim, p.location.second*p.tile_dim), 
				          Point2f((p.location.first + 1)*p.tile_dim, (p.location.second + 1)*p.tile_dim));
		}
	}
}
