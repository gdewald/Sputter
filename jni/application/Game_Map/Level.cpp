#include "Level.h"
#include "Tile.h"

using namespace Zeni;
using namespace std;

const float Level_position::tile_dim = 64.0f;

Level::Level() {
	int dim = 30;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			map[Level_position(i * Level_position::tile_dim, j * Level_position::tile_dim)] = Tile(GRASS_1);
		}
	}
	map[Level_position(4 * Level_position::tile_dim, 4 * Level_position::tile_dim)] = Tile(HOLE_1);
	map_width = dim;
	map_height = dim;
}

void Level::render(Zeni::Point2f pos, float screen_width, float screen_height) {
	for (Level_position p(0, 0); p.location.second < map_height; p.location.second++) {
		for (p.location.first = 0; p.location.first < map_width; p.location.first++) {
			map[p].render(Point2f(p.location.first*p.tile_dim, p.location.second*p.tile_dim), 
				          Point2f((p.location.first + 1)*p.tile_dim, (p.location.second + 1)*p.tile_dim));
		}
	}
}
