#include "Transform.h"


Transform::Transform ():Component(ComponentID::Transform) {
	position.X (0);
	position.Y (0);
}


Transform::~Transform () {
}
