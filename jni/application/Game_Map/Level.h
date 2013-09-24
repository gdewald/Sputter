#pragma once

#include <zenilib.h>
#include <map>
#include <utility>
#include "Tile.h"

class Level_position {
private:
	Level_position();
public:
	std::pair<int, int> location;
	static const float tile_dim;

	bool operator==(const Level_position& rhs) const {
		return ((location.first == rhs.location.first) &&
			    (location.second == rhs.location.second));
	}

	bool operator<(const Level_position& rhs) const {
		return ((location.first < rhs.location.first) ||
				((location.first == rhs.location.first) &&
			     (location.second < rhs.location.second)));
	}

	Level_position(float x, float y) {
		location.first = int(x / tile_dim);
		location.second = int(y / tile_dim);
	}
};

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
		return map_width * Level_position::tile_dim;
	}

	float get_height_px() {
		return map_height * Level_position::tile_dim;
	}
};
