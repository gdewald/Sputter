#pragma once
#include "Game_Objects\Ball.h"
#include "Game_Map\Tile.h"
#include <zenilib.h>

class Collision_2d {
public:
	//Tile collisions
	void on_collision(Ball& b, Terrain_tile& t, Zeni::Point2f tile_pos);

private:

};
