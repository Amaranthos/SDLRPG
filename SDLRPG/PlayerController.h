#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "GameObject.h"

class PlayerController : public GameObject {
public:
	PlayerController ();
	~PlayerController ();

	void Update() override;
};
#endif //PLAYERCONTROLLER_H