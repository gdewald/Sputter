#pragma once
#include <list>
#include <zenilib.h>

//class Collision_object_2d {
//private:
//	Zeni::Point2f position;
//public:
//	Collision_object_2d(Zeni::Point2f position_) : position(position_) { }
//	virtual Zeni::Point2f get_position() {
//		return position;
//	}
//	virtual void set_position(Zeni::Point2f position_) {
//		position = position_;
//	}
//
//	virtual bool intersects(Collision_circle* col_circle, Collision_rectangle* col_rect) {
//		if (col_rect->)
//		return false;
//	}
//
//	virtual void collision(Collision_object_2d* col_object);
//	virtual bool collision_recv(Collision_circle* col_circle);
//	virtual bool collision_recv(Collision_rectangle* col_rect);
//};
//
//class Collision_polygon : public Collision_object_2d {
//private:
//
//};
//
//class Collision_triangle : public Collision_object_2d {
//
//};
//
//
//class Collision_circle : public Collision_object_2d {
//private:
//	float radius;
//public:
//	Collision_circle(Zeni::Point2f position_, float radius_) : Collision_object_2d(position_), radius(radius_) { }
//
//	virtual void collision(Collision_object_2d* col_obj);
//};
//
//class Collision_rectangle : public Collision_object_2d {
//private:
//	float width, height, theta;
//public:
//	Collision_rectangle(Zeni::Point2f position_, float width_, float height_, float theta_ = 0.0f) : 
//		Collision_object_2d(position_), width(width_), height(height_), theta(theta_) { }
//
//	virtual bool collision_recv(Collision_circle* col_circle);
//};
//
//class Collision_Square : public Collision_object_2d {
//	float width;
//};
//
//class Compound_collision_object : public Collision_object_2d {
//	std::list<Collision_object_2d> collision_objects;
//};