#include "Transform.h"


Transform::Transform ():Component(ComponentID::Transform) {
	position.x = 0;
	position.y = 0;
}


Transform::~Transform () {
}

void Transform::operator=(const Transform& item) {
	position = item.position;
	rotation = item.rotation;
}