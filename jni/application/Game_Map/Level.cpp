#include "Level.h"
#include "Tile.h"
#include <cassert>

using namespace Zeni;
using namespace std;

const float Level::tile_dim = 64.0f;

Level::Level() {
	int dim = 30;
	map = new Tile*[dim]();
	for (int i = 0; i < dim; i++) {
		map[i] = new Tile[dim]();
		for (int j = 0; j < dim; j++) {
			map[i][j] = GRASS_1;
		}
	}
	map[20][20] = HOLE_1;
	map_width = dim;
	map_height = dim;
}

void Level::render(Zeni::Point2f pos, float screen_width, float screen_height) {
	int ul_x = (pos.x - screen_width / 2) / tile_dim;
	int ul_y = (pos.y - screen_height / 2) / tile_dim;
	int lr_x = ((pos.x + screen_width / 2) / tile_dim) + 1;
	int lr_y = ((pos.y + screen_height / 2) / tile_dim) + 1;
	
	if (lr_x >= map_width) lr_x = map_width;
	if (lr_y >= map_height) lr_y = map_height;

	assert(ul_x >= 0 && ul_y >= 0);

	//Only render visible tiles(tiles in viewbox)
	for (int i = ul_x; i < lr_x; i++) {
		for (int j = ul_y; j < lr_y; j++) {
			map[i][j].render(Point2f(i*tile_dim, j*tile_dim), 
				             Point2f((i + 1)*tile_dim, (j + 1)*tile_dim));
		}
	}
}
