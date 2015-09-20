#include "GameObject.h"

#include <algorithm>

#include "Component.h"
#include "Transform.h"

GameObject::GameObject () {
	transform = new Transform();
	AddComponent(transform);
}

GameObject::~GameObject () {
	printf ("GameObject Freed");
	Free ();
}

Component* GameObject::GetComponent(ComponentID id){
	auto temp = std::find_if(components.begin(), components.end(), [id](Component* rhs){
		if (!rhs) return false;
		return id == rhs->ID();
	});

	if (temp == components.end()) return nullptr;

	return *temp;
}

void GameObject::AddComponent(Component* comp) {
	components.push_back(comp);
}

void GameObject::RemoveComponent (Component* comp) {
	auto loc = std::find (components.begin (), components.end (), comp);

	if (loc != components.end ()) {
		*loc = components.back ();
		components.pop_back ();
	}
}

//void GameObject::RemoveComponent (ComponentID id) {
//	auto loc = std::find (components.begin (), components.end (), id);
//
//	if (loc != components.end ()) {
//		*loc = components.back ();
//		components.pop_back ();
//	}
//}

void GameObject::Free () {
	for (size_t i = 0; i < components.size (); ++i)
		delete components[i];

	if (transform) delete transform;
}

void GameObject::Update () {

}