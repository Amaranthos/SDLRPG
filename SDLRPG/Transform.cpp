#include "Transform.h"


Transform::Transform ():Component(ComponentID::Transform) {
	position.x = 0;
	position.y = 0;
}


Transform::~Transform () {
}
