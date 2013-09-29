//#pragma once
//#include <zenilib.h>
//#include <list>
//#include <set>
//
//class DCEL_half_edge;
//
//class DCEL_vertex {
//private:
//	Zeni::Point2f coordinates;
//	DCEL_half_edge* incident_edge;
//};
//
//class DCEL_face {
//private:
//	DCEL_half_edge* outer_component;
//	std::list<DCEL_half_edge*> inner_components;
//};
//
//class DCEL_half_edge {
//private:
//	DCEL_vertex* origin;
//	DCEL_half_edge* twin;
//	DCEL_face* incident_face;
//	DCEL_half_edge* next;
//	DCEL_half_edge* prev;
//};
//
//void Voronoi_Diagram(std::set<Zeni::Point2f> points);