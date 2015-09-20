#include "PlayerController.h"

#include <stdio.h>

#include "App.h"
#include "Sprite.h"
#include "Texture.h"
#include "Transform.h"

PlayerController::PlayerController () {
	AddComponent (new Sprite ());
	GetComponent<Sprite> (ComponentID::Sprite)->LoadSprite("img/player.png");

	transform->position = Vec2{ 32,	32 };
	
	width = GetComponent<Sprite> (ComponentID::Sprite)->GetTexture ()->Width ();
	height = GetComponent<Sprite> (ComponentID::Sprite)->GetTexture ()->Height ();

	velocity = 300;

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

	transform->position.x += dVel.x * velocity * App::GetInst ()->DeltaTime ();

	if (transform->position.x < 0) transform->position.x = 0;

	if (transform->position.x > (App::GetInst ()->App::GetInst ()->GetCurrentLevel ()->Width () - width)) transform->position.x = static_cast<float>(App::GetInst ()->App::GetInst ()->GetCurrentLevel ()->Width () - width);

	transform->position.y += dVel.y * velocity * App::GetInst ()->DeltaTime ();

	if (transform->position.y < 0) transform->position.y = 0;

	if (transform->position.y > (App::GetInst ()->App::GetInst ()->GetCurrentLevel ()->Height () - height)) transform->position.y = static_cast<float>(App::GetInst ()->App::GetInst ()->GetCurrentLevel ()->Height () - height);

	App::GetInst ()->MainCamera ()->PositionCam ((static_cast<int>(transform->position.x) + width / 2) - App::GetInst ()->WindowWidth () / 2, (static_cast<int>(transform->position.y) + height / 2) - App::GetInst ()->WindowHeight () / 2);

	GetComponent<Sprite> (ComponentID::Sprite)->GetTexture ()->Render (static_cast<int>(transform->position.x) - App::GetInst ()->MainCamera ()->View ()->x, static_cast<int>(transform->position.y) - App::GetInst ()->MainCamera ()->View ()->y, App::GetInst ()->GetWindow ());
}