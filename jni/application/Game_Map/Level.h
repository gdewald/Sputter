#pragma once

#include <zenilib.h>
#include <map>
#include <utility>
#include "Tile.h"

class Level {
private:
	Tile** map;
	int map_width;
	int map_height;

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
};
