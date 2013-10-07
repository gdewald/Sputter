#include "Level.h"
#include "Tile.h"
#include <cassert>
#include <fstream>

using namespace Zeni;
using namespace std;

const float Level::tile_dim = 64.0f;

Level::Level(String lvl_name) {
	fstream lvl_in("levels\\" + string(lvl_name.c_str()), fstream::in);

	int dim_x, dim_y;
	lvl_in >> dim_x >> dim_y;

	map = new Terrain_tile*[dim_x]();
	for (int i = 0; i < dim_x; i++) {
		map[i] = new Terrain_tile[dim_y]();
		for (int j = 0; j < dim_y; j++) {
			int terrain_type, wall_type;
			lvl_in >> terrain_type >> wall_type;
			map[i][j] = (TERRAIN_ID)terrain_type;
			if (wall_type != -1)
				wall_map[i][j] = (WALL_ID)wall_type;
		}
	}
	
	int event_type;
	while (lvl_in >> event_type && lvl_in.good()) {
		float event_x, event_y;
		lvl_in >> event_x >> event_y;
		switch (event_type) {
		case 0: //Hole_event
			event_map[int(event_x/tile_dim)][int(event_y/tile_dim)].push_back(new Hole_event(Point2f(event_x, event_y)));
		}
	}

	map_width = dim_y;
	map_height = dim_x;
}

Level::Level() {
	int dim = 30;
	map = new Terrain_tile*[dim]();
	for (int i = 0; i < dim; i++) {
		map[i] = new Terrain_tile[dim]();
		for (int j = 0; j < dim; j++) {
			map[i][j] = GRASS_1;
		}
	}
	for (int i = 10; i < 20; i++) {
		for (int j = 3; j < 6; j++) {
			map[i][j] = SAND;
			map[j][i] = ICE;
		}
	}

	for (int i = 3; i < 5; i++) {
		wall_map[0][i] = METAL;
		map[0][i] = ICE;
		wall_map[3][i] = METAL;
		map[3][i] = ICE;
	}
	wall_map[1][0] = METAL;
	map[1][0] = ICE;
	wall_map[2][0] = METAL;
	map[2][0] = ICE;
	wall_map[1][5] = METAL;
	map[1][5] = ICE;
	wall_map[2][5] = METAL;
	map[2][5] = ICE;

	event_map[20][20].push_back(new Hole_event(Point2f(19.5f * 64.0f, 19.5f * 64.0f)));

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


	for (int i = ul_x; i < lr_x; i++) {
		auto& inner_w = wall_map[i];
		auto& inner_e = event_map[i];


		auto ul_w_it = inner_w.upper_bound(ul_y - 1);
		auto lr_w_it = inner_w.lower_bound(lr_y + 1);
		if (ul_w_it != inner_w.end()) {
			for (auto j = ul_w_it; j != lr_w_it; j++) {
				inner_w[j->first].render(Point2f(i * tile_dim, j->first * tile_dim),
					                   Point2f((i + 1) * tile_dim, (j->first + 1)*tile_dim));
			}
		}

		auto ul_e_it = inner_e.upper_bound(ul_y - 2);
		auto lr_e_it = inner_e.lower_bound(lr_y + 2);
		if (ul_e_it != inner_e.end()) {
			for (auto j = ul_e_it; j != lr_e_it; j++) {
				for_each(inner_e[j->first].begin(), inner_e[j->first].end(), [](Ball_event* b){ b->render(); });
			}
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
		auto t = get_tile(cur_pos);
		b->set_friction(t->get_friction());

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

void Level::check_event_collisions(Ball* b) {
	auto cur_pos = b->get_position();
	int x_coor = get_coordinate(cur_pos.x - 32.0f) - 1;
	int y_coor = get_coordinate(cur_pos.y - 32.0f) - 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			auto& inner = event_map[x_coor + i][y_coor + j];
			for_each(inner.begin(), inner.end(), [b](Ball_event* e){ if (e->is_colliding(b)) { e->perform_collision(b); }});
		}
	}


}


//find where the sphere should touch the square
float Level::get_theta_wall(Collision::Sphere col_sphere_new, Collision::Sphere col_sphere_old, Collision::Parallelepiped col_square) {
	Point2f sphere_pos(col_sphere_new.get_center());
	float sphere_rad = col_sphere_new.get_radius();
	Point2f square_pos(col_square.get_center());
	float theta = Vector2f(square_pos - sphere_pos).theta();
	if (theta < 0)
		theta = -(theta + 3.14) + 6.28;

	if (theta >((3.14f * 7) / 4) && theta < (3.14f * 5) / 4) { //Left
		return (3.14f * 3) / 2;
	}
	if (theta < ((3.14f * 3) / 4) && theta > 3.14f / 4) { //Right
		return 3.14f / 2;
	}
	if (theta < ((3.14f * 5) / 4) && theta > ((3.14f * 3) / 4)) { //Top
		return 0.0f;
	}
	if (theta >= 0.0f && theta < 3.14f / 4 || theta <= 6.28f && theta > ((3.14f * 7) / 4)) { //Bottom
		return 3.14f;
	}
}
