#include "Camera.h"

#include "App.h"

Camera::Camera (int width, int height) {
	view.w = width;
	view.h = height;
	view.x = 0;
	view.y = 0;
}


Camera::~Camera () {

}

void Camera::PositionCam (int x, int y) {
	view.x = x;
	view.y = y;

	CheckBounds ();
}

void Camera::CheckBounds () {
	if (view.x < 0) view.x = 0;
	if (view.y < 0) view.y = 0;
	if (view.x > App::levelWidth - view.w) view.x = App::levelWidth - view.w;
	if (view.y > App::levelHeight - view.h) view.y = App::levelHeight - view.h;
}
