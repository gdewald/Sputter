#pragma once

#include <zenilib.h>
#include "../Game_Objects/Ball.h"
#include <vector>
#include <map>
#include <utility>

enum TERRAIN_ID { GRASS_1, SAND, ICE, NOTERRAIN };
enum WALL_ID { METAL, WOOD_1, WOOD_2, NOWALL };
enum TILE_TYPE { START, FINISH, NOTYPE };
const float TILE_FRICT[3] = { 200.0f, 400.0f, 100.0f };

//class Tile_factory {
//private:
//public:
//};

class Tile {
public:
	virtual void render(Zeni::Point2f ul, Zeni::Point2f lr, Zeni::String tile_str);
};

class Wall_tile: public Tile {
private:
	WALL_ID id;
	bool alive;
public:
	Wall_tile() : id(NOWALL) {}
	Wall_tile(WALL_ID w_id) : id(w_id) { }
	const Wall_tile& operator=(const WALL_ID w_id) { id = w_id; return *this; }
	//If false, tile should be destroyed
	bool on_collision(Ball* b);
	void render(Zeni::Point2f ul, Zeni::Point2f lr);
};

class Terrain_tile: public Tile {
private:
	TERRAIN_ID id;
	bool active;
	TILE_TYPE type;

	Zeni::Collision::Parallelepiped col_square;
public:
	Terrain_tile(const Terrain_tile& t) : id(t.id), active(false) { }
	Terrain_tile() : id(NOTERRAIN), active(false) { }
	Terrain_tile(TERRAIN_ID id_) : id(id_), active(false) { }

	bool is_active() { return active; }
	float get_friction() { return TILE_FRICT[id]; }

	const Terrain_tile& operator=(const TERRAIN_ID t_id) { id = t_id; return *this; }

	void render(Zeni::Point2f ul, Zeni::Point2f lr);
};
