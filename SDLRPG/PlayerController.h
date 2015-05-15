#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "GameObject.h"
#include "Vec2.h"

class PlayerController : public GameObject {
public:
	PlayerController ();
	~PlayerController ();

	static const int Width = 64;
	static const int Height = 64;

	static const int Velocity = 600;

	void Update() override;

private:
	Vec2 dVel;
};
#endif //PLAYERCONTROLLER_H