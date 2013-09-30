#pragma once

#include <zenilib.h>
#include <map>

enum TILE_ID { GRASS_1, HOLE_1, SAND, NONE };
enum TILE_TYPE { START, FINISH };
const Zeni::String TILE_STR[3] = {"grass_1", "hole_1", "hole_1"};
const float TILE_FRICT[3] = { 200.0f, 200.0f, 350.0f };

class Tile {
private:
	TILE_ID id;
	bool active;
	TILE_TYPE type;

	float tile_friction = 200.0f;

public:
	Tile(const Tile& t) : id(t.id), active(false) {}
	Tile() : id(NONE), active(false) {}
	Tile(TILE_ID id_) : id(id_), active(false) { }

	bool is_active() { return active; }
	float get_friction() { return TILE_FRICT[id]; }

	const Tile& operator=(const TILE_ID t_id) { id = t_id; return *this; }

	void render(Zeni::Point2f ul, Zeni::Point2f lr);
};
