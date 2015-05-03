#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
	Vec2 ();
	~Vec2 ();



	float X () { return x; }
	float Y () { return y; }

	void X (float x) { this->x = x; }
	void Y (float y) { this->y = y; }

private:
	float x;
	float y;
};
#endif //VEC@_H