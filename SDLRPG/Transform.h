#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Vec2.h"

class Transform : public Component {
public:
	Transform ();
	~Transform ();

	Vec2 Position() const { return position;}
	void Position(Vec2 position) { this->position = position; }

	float Rotation() const { return rotation; }
	void Rotation(float rotation) { this->rotation = rotation; }
private:
	Vec2 position;
	float rotation;
};
#endif //TRANSFORM_H