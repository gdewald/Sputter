#include "Level.h"
#include "Tile.h"
#include <cassert>

using namespace Zeni;
using namespace std;

const float Level::tile_dim = 64.0f;

Level::Level() {
	int dim = 30;
	map = new Terrain_tile*[dim]();
	for (int i = 0; i < dim; i++) {
		map[i] = new Terrain_tile[dim]();
		for (int j = 0; j < dim; j++) {
			map[i][j] = GRASS_1;
		}
	}
	map[20][20] = HOLE_1;
	for (int i = 10; i < 20; i++) {
		for (int j = 3; j < 6; j++) {
			map[i][j] = SAND;
			map[j][i] = ICE;
		}
	}

	for (int i = 5; i < 10; i++) {
		wall_map[5][i] = METAL;
		map[5][i] = ICE;
		wall_map[8][i] = METAL;
		map[8][i] = ICE;
	}
	wall_map[6][10] = METAL;
	map[6][10] = ICE;
	wall_map[7][10] = METAL;
	map[7][10] = ICE;


	map_width = dim;
	map_height = dim;
}

void Level::render(Zeni::Point2f pos, float screen_width, float screen_height) {
	int ul_x = (pos.x - screen_width / 2) / tile_dim;
	int ul_y = (pos.y - screen_height / 2) / tile_dim;
	int lr_x = ((pos.x + screen_width / 2) / tile_dim) + 1;
	int lr_y = ((pos.y + screen_height / 2) / tile_dim) + 1;
	
	if (lr_x >= map_width) lr_x = map_width;
	if (lr_y >= map_height) lr_y = map_height;

	assert(ul_x >= 0 && ul_y >= 0);

	//Only render visible tiles(tiles in viewbox)
	for (int i = ul_x; i < lr_x; i++) {
		for (int j = ul_y; j < lr_y; j++) {
			map[i][j].render(Point2f(i*tile_dim, j*tile_dim), 
				             Point2f((i + 1)*tile_dim, (j + 1)*tile_dim));
		}
	}
}

Collision::Parallelepiped Level::get_col_box(int x, int y) {
	Point3f tile_pos(x * 64.0f, y * 64.0f, 0.0f);
	Vector3f a(64.0f, 0.0f, 0.0f);
	Vector3f b(0.0f, 64.0f, 0.0f);
	Vector3f c(0.0f, 0.0f, 1.0f);
	return Collision::Parallelepiped(tile_pos, a, b, c);
}

void Level::check_terrain(Ball* b) {
	auto cur_pos = b->get_position();
	if (get_coordinate(cur_pos.x) != get_coordinate(last_pos.x) || get_coordinate(cur_pos.y) != get_coordinate(last_pos.y)) {
		b->set_friction(get_tile(cur_pos)->get_friction());
		last_pos = cur_pos;
	}
}

float Level::check_tile_collisions(Ball* b, float dist) {
	auto col_sphere = b->get_col_sphere();
	auto cur_pos = b->get_position();
	int x_coor = get_coordinate(cur_pos.x - 32.0f);
	int y_coor = get_coordinate(cur_pos.y - 32.0f);
	Collision::Parallelepiped col_square;

	//This should only be relevant if dist is non-zero
	static Collision::Parallelepiped final_col_square;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
				auto& inner = wall_map[x_coor + i];
				auto it = inner.find(y_coor + j);
				if (it != inner.end()) {
					col_square = get_col_box(x_coor + i, y_coor + j);
					//Check if collision happens
					if (col_sphere.intersects(col_square)) {
						final_col_square = col_square;
						//Move ball out of the collision
						dist += b->move_from_col(col_sphere, col_square);
						
						// Check consequitive collision, keep track of distance
						return check_tile_collisions(b, dist);
					}
				}
		}
	}
	
	// Reflect ball if distance is non-zero
	if (dist > 0.0f) {
		float theta_wall = get_theta_wall(b->get_col_sphere(), col_sphere, final_col_square);
		b->reflect(theta_wall, dist);
	}

	return 0.0f;
}

//find where the sphere should touch the square
float Level::get_theta_wall(Collision::Sphere col_sphere_new, Collision::Sphere col_sphere_old, Collision::Parallelepiped col_square) {
	Point2f sphere_pos(col_sphere_new.get_center());
	float sphere_rad = col_sphere_new.get_radius();
	Point2f square_pos(col_square.get_center());
	float theta = Vector2f(square_pos - sphere_pos).theta();

	if (theta >((-3.14f * 3) / 4) && theta < -3.14f / 4) { //Left
		return (3.14f * 3) / 2;
	}
	if (theta < ((3.14f * 3) / 4) && theta > 3.14f / 4) { //Right
		return 3.14f / 2;
	}
	if (theta < ((-3.14f * 3) / 4) || theta > ((3.14f * 3) / 4)) { //Top
		return 0.0f;
	}
	if (theta < 3.14f / 4 || theta > -3.14f / 4) { //Bottom
		return 3.14f;
	}
}
