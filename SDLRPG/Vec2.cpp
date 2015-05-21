#include "Vec2.h"

#include <cmath>

Vec2 Vec2::Normalized () {
	float length = Length ();

	Vec2 temp = Vec2();

	if (length != 0) {
		temp.x = x / length;
		temp.y = y / length;
	}
	else {
		temp.x = 0;
		temp.y = 0;
	}

	return temp;
}

void Vec2::Normalize () {
	float length = Length();
	
	if (length != 0) {
		x = x / length;
		y = y / length;
	}
}

float Vec2::Length () {
	return sqrt (x*x + y*y);
}
