#include "Game_Model.h"
#include <cassert>

using namespace Zeni;
using namespace std;

Game_Model* Game_Model::model;

void Game_Model::initialize() {
	b = new Ball(Point2f());
}

void Game_Model::update() {
	assert(b);
	//b->update();
}
