#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
	float x;
	float y;

	Vec2() { x = 0; y = 0; }
	Vec2(float x, float y) { this->x = x; this->y = y; }

	float Length ();
	Vec2 Normalized ();
	void Normalize ();
};
#endif //VEC2_H