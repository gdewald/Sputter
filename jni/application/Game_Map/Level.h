#pragma once

#include <zenilib.h>
#include <map>
#include <utility>
#include <cassert>
#include "Tile.h"
#include "../Game_Objects/Ball.h"

class Level {
private:
	Tile** map;
	int map_width;
	int map_height;

	Zeni::Point2f last_pos;

	static const float tile_dim;

public:
	//Default level
	Level();
	//Level from file
	Level(Zeni::String lvl_name);

	//Render the visible tiles
	void render(Zeni::Point2f pos, float screen_width, float screen_height);

	float get_width_px() {
		return map_width * tile_dim;
	}

	float get_height_px() {
		return map_height * tile_dim;
	}

	Tile* get_tile(Zeni::Point2f pos) {
		assert(pos.x >= 0 && pos.y >= 0);
		return &map[int(pos.x / tile_dim)][int(pos.y / tile_dim)];
	}

	void check_terrain(Ball* b);
};
