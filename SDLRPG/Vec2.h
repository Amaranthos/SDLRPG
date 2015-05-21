#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
	float x;
	float y;

	float Length ();
	Vec2 Normalized ();
	void Normalize ();
};
#endif //VEC2_H