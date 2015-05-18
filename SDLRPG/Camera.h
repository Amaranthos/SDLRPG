#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

#include "Vec2.h"

class Camera {
public:
	Camera (int width, int height);
	~Camera ();

	void PositionCam(int x, int y);
	void MoveCam (int x, int y);

	void CheckBounds ();

	SDL_Rect* View () { return &view; }

private:
	SDL_Rect view;
	Vec2 target;
};
#endif //CAMERA_H