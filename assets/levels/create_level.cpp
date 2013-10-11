#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int** terrain_map;
int** wall_map;
void fill_areas(const string& choices, int** map);

int main() {
	//Get name for level
	string filename;
	cout << "Enter level name: " ;
	cin >> filename; 
	fstream lvl_out(filename.c_str(), fstream::out);
	
	int par;
	cout << endl <<"Enter par: ";
	cin >> par;
	lvl_out << par << endl;
	
	int dim_x, dim_y;
	cout << endl << "Enter map dimensions(2 integers): ";
	cin >> dim_x >> dim_y;
	//lvl_out << "#Tile dimensions" << endl;
	lvl_out << dim_x << " " << dim_y << endl << endl;
	
	int fill;
	cout << endl << "Select terrain map fill(0 - grass, 1 - sand, 2 - ice): ";
	cin >> fill;
	terrain_map = new int*[dim_x];
	wall_map = new int*[dim_x];
	for(int i = 0; i < dim_x; i++) {
		terrain_map[i] = new int[dim_y];
		wall_map[i] = new int[dim_y];
		for(int j = 0; j < dim_y; j++) {
			terrain_map[i][j] = fill;
			wall_map[i][j] = -1;
		}
	}
	
	//Print map to file
	fill_areas(", 0 - grass, 1 - sand, 2 - ice", terrain_map);
	fill_areas(", 0 - metal, 1 - wood", wall_map);
	for(int i = 0; i < dim_x; i++) {
		for(int j = 0; j < dim_y; j++) {
			lvl_out /*<< "("*/ << terrain_map[i][j] << " " << /*"," <<*/ wall_map[i][j] << " "/*<< ") "*/;
		}
		lvl_out << endl;
	}
	lvl_out << endl;
	
	cout << endl << "Enter event type(-1 - end, 0 - hole, 1 - powerball, 2 - spikeball, 3 - fireball, 4 - spawn): ";
	int event;
	while(cin >> event && event != -1) {
		float pos_x, pos_y;
		cin >> pos_x >> pos_y;
		lvl_out << event << " " << pos_x << " " << pos_y << endl;
		cout << endl << "Enter event type(-1 - end, 0 - hole, 1 - powerball, 2 - spikeball, 3 - fireball, 4 - spawn): ";
	}
	lvl_out.close();
}

void fill_areas(const string& choices, int** map) {
	int fill;
	cout << endl << "Select area fill(-1 - end" << choices << "): ";
	cin >> fill;
	
	if (fill == -1) return;
	
	int start_x, start_y, end_x, end_y;
	cout << endl << "Enter start and end location(upper left -> lower right): ";
	cin >> start_x >> start_y >> end_x >> end_y;
	for(int i = start_x; i <= end_x; i++) {
		for(int j = start_y; j <= end_y; j++) {
			map[i][j] = fill;
		}
	}
	fill_areas(choices, map);
}