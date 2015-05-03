#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include "ComponentID.h"
#include "Component.h"
#include "Transform.h"

class GameObject {
public:
	GameObject ();
	virtual ~GameObject ();

	Component *GetComponent (ComponentID id);
	void AddComponent (Component* comp);
	bool HasComponent (ComponentID id);

private:
	std::vector<Component*> components;
};
#endif //GAMEOBJECT_H