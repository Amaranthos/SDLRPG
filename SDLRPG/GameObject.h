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
	void RemoveComponent (Component* comp);
	void RemoveComponent (ComponentID id);
	bool HasComponent (ComponentID id);

	int Width () const { return width; }
	int Height () const { return height; }

	template <typename T>
	T* GetComponent (ComponentID id);
protected:
	std::vector<Component*> components;
	Transform* transform;

	int width;
	int height;
};

template <typename T>
T* GameObject::GetComponent (ComponentID id) {
	return (T*)GetComponent (id);
}
#endif //GAMEOBJECT_H