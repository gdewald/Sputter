#pragma once
#include <list>

class Collision_object_2d {

};

class Collision_triangle : public Collision_object_2d {

};

class Collision_Rectangle : public Collision_object_2d {

};

class Collision_circle : public Collision_object_2d {

};

class Compound_collision_object : public Collision_object_2d {
	std::list<Collision_object_2d> collision_objects;
};