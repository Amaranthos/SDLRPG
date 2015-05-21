#include "PlayerController.h"

#include <stdio.h>

#include "App.h"
#include "Sprite.h"
#include "Transform.h"

PlayerController::PlayerController () {
	AddComponent (new Sprite ());
	GetComponent<Sprite> (ComponentID::Sprite)->LoadSprite("img/player.png");
	
	dVel.x = 0;
	dVel.y = 0;
}


PlayerController::~PlayerController () {

}

void PlayerController::Update() {
	dVel.x = 0;
	dVel.y = 0;

	if (App::GetInst()->KeyStates()[SDL_SCANCODE_W]) dVel.y = -1;

	if (App::GetInst ()->KeyStates ()[SDL_SCANCODE_A]) dVel.x = -1;

	if (App::GetInst ()->KeyStates ()[SDL_SCANCODE_S]) dVel.y = 1;

	if (App::GetInst ()->KeyStates ()[SDL_SCANCODE_D]) dVel.x = 1;

	dVel.Normalize ();

	transform->position.x += dVel.x * Velocity * App::GetInst ()->DeltaTime ();

	if (transform->position.x < 0) transform->position.x = 0;

	if (transform->position.x > (App::GetInst ()->levelWidth - Width)) transform->position.x = (App::GetInst ()->levelWidth - Width);

	transform->position.y += dVel.y * Velocity * App::GetInst ()->DeltaTime ();

	if (transform->position.y < 0) transform->position.y = 0;

	if (transform->position.y > (App::GetInst ()->levelHeight - Height)) transform->position.y = (App::GetInst ()->levelHeight - Height);

	App::GetInst ()->MainCamera ()->PositionCam ((transform->position.x + Width / 2) - App::GetInst ()->WindowWidth () / 2, (transform->position.y + Height / 2) - App::GetInst ()->WindowHeight () / 2);

	GetComponent<Sprite> (ComponentID::Sprite)->GetTexture ()->Render (transform->position.x - App::GetInst ()->MainCamera ()->View ()->x, transform->position.y - App::GetInst ()->MainCamera ()->View ()->y, App::GetInst ()->GetWindow ());
}