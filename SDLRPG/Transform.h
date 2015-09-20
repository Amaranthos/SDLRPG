#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Vec2.h"

class Transform : public Component {
public:
	Transform ();
	~Transform ();

	Vec2 position;
	float rotation;

	void operator=(const Transform& item);
};
#endif //TRANSFORM_H