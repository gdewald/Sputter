#include "Tile.h"
#include "../Points.h"

using namespace std;
using namespace Zeni;

std::map<TERRAIN_ID, Zeni::String> fill_map_t() {
	std::map<TERRAIN_ID, Zeni::String> m;
	m[GRASS_1] = "grass_1";
	m[SAND] = "sand_1";
	m[ICE] = "ice_1";
	m[NOTERRAIN] = "";
	return m;
}
std::map<WALL_ID, Zeni::String> fill_map_w() {
	std::map<WALL_ID, Zeni::String> m;
	m[METAL] = "sheetmetal";
	m[WOOD_1] = "wood_1";
	m[WOOD_2] = "wood_2";
	m[NOWALL] = "";
	return m;
}

std::map<TERRAIN_ID, Zeni::String> TILE_STR_T = fill_map_t();
std::map<WALL_ID, Zeni::String> TILE_STR_W = fill_map_w();

void Tile::render(Point2f ul, Point2f lr, String tile_str) {
	Video& vr = get_Video();

	Vertex2f_Texture v1 = Vertex2f_Texture(ul, Point2f());
	Vertex2f_Texture v2 = Vertex2f_Texture(Point2f(lr.x, ul.y), Point2f(1.0f, 0.0f));
	Vertex2f_Texture v3 = Vertex2f_Texture(lr, Point2f(1.0f, 1.0f));
	Vertex2f_Texture v4 = Vertex2f_Texture(Point2f(ul.x, lr.y), Point2f(0.0f, 1.0f));

	Quadrilateral<Vertex2f_Texture> quad = Quadrilateral<Vertex2f_Texture>(v1, v2, v3, v4);
	Material mat = Material(tile_str);
	quad.fax_Material(&mat);

	vr.render(quad);
}

void Terrain_tile::render(Zeni::Point2f ul, Zeni::Point2f lr) {
	Tile::render(ul, lr, TILE_STR_T[id]);
}

void Wall_tile::render(Zeni::Point2f ul, Zeni::Point2f lr) {
	Tile::render(ul, lr, TILE_STR_W[id]);
}

bool Wall_tile::on_collision(Ball* b) {
	switch (id) {
	case METAL:
		//Tink sound
		break;
	case WOOD_1:
		if (b->get_speed() < 150.0f)
			break;
		else if (b->is_fireball()) {
			Points::get_Points().wall_break();
			return false;
		}

		Points::get_Points().wall_damage();
		//Crunch sound
		id = WOOD_2;
		break;
	case WOOD_2:
		Points::get_Points().wall_break();
		//Break sound
		return false;
		break;
	}
	return true;
}
