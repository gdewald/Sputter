#pragma once

#include <zenilib.h>
#include <map>
#include <set>
#include <utility>
#include <cassert>
#include "Tile.h"
#include "../Game_Objects/Ball.h"
#include "../Game_Objects/Ball_event.h"

class Level {
private:
	//Tile structure
	Terrain_tile** map;
	int map_width;
	int map_height;

	std::map<int, std::map<int, Wall_tile>> wall_map;

	//Objects outside the tile structure
	std::map <int, std::map<int, std::vector<Ball_event*>>> event_map;

	Zeni::Point2f last_pos;
	//Only used for arrow logic
	Zeni::Point2f hole_pos;

	static const float tile_dim;

public:
	//Default level
	Level();
	//Level from file
	Level(Zeni::String lvl_name, Ball* b);

	//Render the visible tiles
	void render(Zeni::Point2f pos, float screen_width, float screen_height);

	float get_width_px() {
		return map_width * tile_dim;
	}

	float get_height_px() {
		return map_height * tile_dim;
	}

	Terrain_tile* get_tile(Zeni::Point2f pos) {
		assert(pos.x >= 0 && pos.y >= 0);
		return &map[get_coordinate(pos.x)][get_coordinate(pos.y)];
	}

	int get_coordinate(float pos) {
		return pos / tile_dim;
	}

	//Collision stuff
	Zeni::Collision::Parallelepiped get_col_box(int x, int y);
	float check_tile_collisions(Ball* b, float dist = 0.0f);
	void check_event_collisions(Ball* b);
	float get_theta_wall(Zeni::Collision::Sphere col_sphere_new, Zeni::Collision::Sphere col_sphere_old, Zeni::Collision::Parallelepiped col_square);
		
	void check_terrain(Ball* b);
};