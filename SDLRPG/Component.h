#ifndef COMPONENT_H
#define COMPONENT_H

#include "ComponentID.h"

class Component {
public:
	Component (ComponentID id);
	virtual ~Component ();

	ComponentID ID() { return id; }

	void operator=(const Component& item);

protected:
	const ComponentID id;

private:
};
#endif //COMPONENT_H