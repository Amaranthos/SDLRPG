#include "PlayerController.h"

#include "App.h"
#include "Sprite.h"
#include "Transform.h"

PlayerController::PlayerController () {
	AddComponent (new Sprite ());
	static_cast<Sprite*>(GetComponent (ComponentID::Sprite))->LoadSprite ("img/player.png");
}


PlayerController::~PlayerController () {

}

void PlayerController::Update() {
	if (App::GetInst()->KeyStates()[SDL_SCANCODE_D]) {

	}

	static_cast<Sprite*>(GetComponent (ComponentID::Sprite))->GetTexture()->Render(&transform->Position(), App::GetInst()->GetWindow());
}