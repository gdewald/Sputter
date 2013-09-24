#pragma once

#include <zenilib.h>
#include <map>

enum TILE_ID { GRASS_1, HOLE_1, NONE };
const Zeni::String TILE_STR[2] = {"grass_1", "hole_1"};

class Tile {
private:
	TILE_ID id;

public:
	Tile(const Tile& t) : id(t.id) {}
	Tile() : id(NONE) {}
	Tile(TILE_ID id_) : id(id_) { }

	const Tile& operator=(const TILE_ID t_id) { id = t_id; return *this; }

	void render(Zeni::Point2f ul, Zeni::Point2f lr);
};
