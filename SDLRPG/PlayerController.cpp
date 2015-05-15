#include "PlayerController.h"

#include <stdio.h>

#include "App.h"
#include "Sprite.h"
#include "Transform.h"

PlayerController::PlayerController () {
	AddComponent (new Sprite ());
	static_cast<Sprite*>(GetComponent (ComponentID::Sprite))->LoadSprite ("img/player.png");

	dVel.x = 0;
	dVel.y = 0;
}


PlayerController::~PlayerController () {

}

void PlayerController::Update() {
	if (App::GetInst()->KeyStates()[SDL_SCANCODE_W]) dVel.y += Velocity;
	else dVel.y -= Velocity;

	if (App::GetInst ()->KeyStates ()[SDL_SCANCODE_A]) dVel.x -= Velocity;
	else dVel.x += Velocity;

	if (App::GetInst ()->KeyStates ()[SDL_SCANCODE_S]) dVel.y -= Velocity;
	else dVel.y += Velocity;

	if (App::GetInst ()->KeyStates ()[SDL_SCANCODE_D]) dVel.x += Velocity;
	else dVel.x -= Velocity;

	transform->position.x += dVel.x * App::GetInst ()->DeltaTime ();

	if (transform->position.x < 0) transform->position.x = 0;

	if (transform->position.x > (App::GetInst ()->WindowWidth() - Width)) transform->position.x = (App::GetInst ()->WindowWidth() - Width);

	transform->position.y += dVel.y * App::GetInst ()->DeltaTime ();

	if (transform->position.y < 0) transform->position.y = 0;

	if (transform->position.y > (App::GetInst ()->WindowHeight() - Height)) transform->position.y = (App::GetInst ()->WindowHeight() - Height);

	static_cast<Sprite*>(GetComponent (ComponentID::Sprite))->GetTexture()->Render(&transform->position, App::GetInst()->GetWindow());
}