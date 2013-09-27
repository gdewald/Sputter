#pragma once

#include <zenilib.h>
#include <map>

enum TILE_ID { GRASS_1, HOLE_1, NONE };
enum TILE_TYPE { START, FINISH };
const Zeni::String TILE_STR[2] = {"grass_1", "hole_1"};

class Tile {
private:
	TILE_ID id;
	bool active;
	TILE_TYPE type;

public:
	Tile(const Tile& t) : id(t.id), active(false) {}
	Tile() : id(NONE), active(false) {}
	Tile(TILE_ID id_) : id(id_), active(false) { }

	bool is_active() { return active; }

	const Tile& operator=(const TILE_ID t_id) { id = t_id; return *this; }

	void render(Zeni::Point2f ul, Zeni::Point2f lr);
};
