#pragma once
#include <zenilib.h>
#include "Game_Objects\Ball.h"

using namespace Zeni;
using namespace std;

class Controller {
private:
	//Ball under control
	Ball* ball;
	// Raw inputs
	float x, y, ltr, rtr;
	void process_inputs();
	// Processed inputs
	float spread, range_mult, range_base, theta;

	Controller();

public:
	Controller(Ball* ball_) : ball(ball_) {}

	void set_x(float x_) { x = x_; }
	void set_y(float y_) { y = y_; }
	void set_ltr(float ltr_) { ltr = ltr_; }
	void set_rtr(float rtr_) { rtr = rtr_; }
	void fire();


	void render();
};
