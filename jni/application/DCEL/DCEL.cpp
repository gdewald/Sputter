//#include "DCEL.h"
//#include <queue>
//
//using namespace std;
//using namespace Zeni;
//
//struct site_event {
//	bool circle_event;
//	Point2f pos;
//};
//struct cmp_y {
//	bool operator() (const site_event& e1, const site_event& e2) {
//		return (e1.pos.y < e2.pos.y);
//	}
//};
//struct cmp_x {
//	bool operator() (const site_event& e1, const site_event& e2) {
//		return (e1.pos.x < e2.pos.x);
//	}
//};
//
//struct status_leaf {
//	site_event* circle_event;
//	DCEL_half_edge* e;
//};
//
//void handle_site_event(site_event& e, priority_queue<site_event, vector<site_event>, cmp_y>& event_queue, map<site_event, status_leaf, cmp_x>& status_struct);
//void handle_circle_event(site_event& e, priority_queue<site_event, vector<site_event>, cmp_y>& event_queue, map<site_event, status_leaf, cmp_x>& status_struct);
//
//void Voronoi_Diagram(set<Point2f> points) {
//	priority_queue<site_event, vector<site_event>, cmp_y> event_queue;
//	map<Point2f, status_leaf, cmp_x> status_map;
//	DCEL_vertex* v = nullptr;
//
//	for(auto p = points.begin(); p != points.end(); p++) {
//		site_event e;
//		e.pos = *p;
//		e.circle_event = false;
//		event_queue.push(e);
//	}
//
//	while(!event_queue.empty()) {
//		site_event e = event_queue.top();
//		event_queue.pop();
//		if(!e.circle_event) {
//			handle_site_event(e, event_queue, status_map);
//		}
//		else handle_circle_event(e, event_queue, status_map);
//	}
//}
//
//void handle_site_event(site_event& e, priority_queue<site_event, vector<site_event>, cmp_y>& event_queue, map<site_event, status_leaf, cmp_x>& status_struct) {
//	if(status_map.empty()) {
//		status_leaf l;
//		l.circle_even = nullptr;
//		l.e = nullptr;
//		status_map[e.pos] = l;
//		return;
//	}
//
//
//}
//
////void handle_circle_event(site_event& e, priority_queue<site_event, vector<site_event>, cmp_y>& event_queue, map<site_event, status_leaf, cmp_x>& status_struct);
