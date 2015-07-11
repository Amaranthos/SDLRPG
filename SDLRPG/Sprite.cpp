#include "Sprite.h"

#include "Texture.h"
#include "App.h"

Sprite::Sprite() : Component(ComponentID::Sprite) {
	texture = new Texture();
}

Sprite::~Sprite() {
	delete texture;
}

void Sprite::LoadSprite(const std::string& path) {
	texture = App::GetInst ()->GetTextureManager ()->GetTexture (path);
}