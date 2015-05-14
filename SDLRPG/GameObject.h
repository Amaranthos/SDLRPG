#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include "ComponentID.h"

class Component;
class Transform;

class GameObject {
public:
	GameObject ();
	virtual ~GameObject ();

	virtual void Update();
	virtual void Free ();

	Component* GetComponent (ComponentID id);
	void AddComponent (Component* comp);
	bool HasComponent (ComponentID id);

protected:
	std::vector<Component*> components;
	Transform* transform;
};
#endif //GAMEOBJECT_H