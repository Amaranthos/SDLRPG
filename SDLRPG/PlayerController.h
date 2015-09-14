#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "GameObject.h"
#include "Vec2.h"

class PlayerController : public GameObject {
public:
	PlayerController ();
	~PlayerController ();

	void Update() override;

	int Velocity () const { return velocity; }
private:
	Vec2 dVel;

	int velocity;
};
#endif //PLAYERCONTROLLER_H