#include "PlayerController.h"

#include "App.h"

PlayerController::PlayerController () {

}


PlayerController::~PlayerController () {

}

void PlayerController::Update() {
	if (App::GetInst()->KeyStates()[SDL_SCANCODE_D]) {

	}
}