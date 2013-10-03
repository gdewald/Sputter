#pragma once

#include <zenilib.h>
#include <vector>
#include <map>

enum TERRAIN_ID { GRASS_1, HOLE_1, SAND, ICE, NONE };
enum WALL_ID { METAL, WOOD, NOWALL };
enum TILE_TYPE { START, FINISH };
const std::vector<Zeni::String> TILE_STR = {"grass_1", "hole_1", "sand_1", "ice_1"};
const std::vector<float> TILE_FRICT = { 200.0f, 200.0f, 400.0f, 100.0f };

//class Tile_factory {
//private:
//public:
//};

class Wall_tile {
private:
	WALL_ID id;
	bool alive;
public:
	Wall_tile() : id(NOWALL) {}
	Wall_tile(WALL_ID w_id) : id(w_id) { }
	const Wall_tile& operator=(const WALL_ID w_id) { id = w_id; return *this; }
};

class Terrain_tile {
private:
	TERRAIN_ID id;
	bool active;
	TILE_TYPE type;

	float tile_friction = 200.0f;
	Zeni::Collision::Parallelepiped col_square;

public:
	Terrain_tile(const Terrain_tile& t) : id(t.id), active(false) {}
	Terrain_tile() : id(NONE), active(false) {}
	Terrain_tile(TERRAIN_ID id_) : id(id_), active(false) { }

	bool is_active() { return active; }
	float get_friction() { return TILE_FRICT[id]; }

	const Terrain_tile& operator=(const TERRAIN_ID t_id) { id = t_id; return *this; }

	void render(Zeni::Point2f ul, Zeni::Point2f lr);
};
