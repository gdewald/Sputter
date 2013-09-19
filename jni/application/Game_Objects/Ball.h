#pragma once

#include "zenilib.h"

using namespace Zeni;
using namespace std;

class Ball {
private:
	Point2f position;
	float v;
	float a;

public:
	Ball() : position(0.0f, 0.0f), v(0.0f), a(0.0f) { }
	void update();
};