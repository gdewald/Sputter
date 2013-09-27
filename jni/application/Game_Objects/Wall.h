#pragma once
#include <zenilib.h>
#include <utility>
//#include "Collision_object\Collision_object_2d.h"

class Wall /*: public Collision_rectangle*/ {
private:
	Zeni::Point2f position;
	Zeni::String texture_name;
	float texture_width;
	float texture_height;
	float theta;

	//Collision_object_2d* col_obj;
	Wall();
public:
	Wall(Zeni::Point2f position_, Zeni::String texture_name_, float texture_height_, float texture_width_, float theta_ = 0.0f) : 
		/*Collision_rectangle(position_, texture_width_, texture_height_, theta_),*/ position(position_), texture_name(texture_name_), texture_height(texture_height_), texture_width(texture_width_), theta(theta_) { }
	void render();
};