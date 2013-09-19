#pragma once

#include <zenilib.h>
#include "Game_Objects\Ball.h"

using namespace Zeni;
using namespace std;

class Game_Model {
private:
	static Game_Model* model;
	Ball* b;

	void initialize();
	
	Game_Model() {
		model = nullptr;
		initialize();
	}
	~Game_Model();
public:
	static Game_Model& get_instance() {
		if (!model) model = new Game_Model(); 
		return *model; 
	}

	void update();

};