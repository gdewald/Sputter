#include "Tile.h"

using namespace std;
using namespace Zeni;

std::map<TERRAIN_ID, Zeni::String> TILE_STR_T{ std::make_pair(GRASS_1, "grass_1"), std::make_pair(HOLE_1, "hole_1"), std::make_pair(SAND, "sand_1"),
std::make_pair(ICE, "ice_1"), std::make_pair(NOTERRAIN, "") };
std::map<WALL_ID, Zeni::String> TILE_STR_W{ std::make_pair(METAL, "sheetmetal"), std::make_pair(WOOD, "wood_1"), std::make_pair(NOWALL, "") };

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
