#include "Sprite.h"

Sprite::Sprite() : Component(ComponentID::Sprite) {
	texture = new Texture();
}

Sprite::~Sprite() {
	delete texture;
}

void Sprite::LoadSprite(std::string path) {
	texture->LoadFromFile(path, App::GetInst()->GetWindow());
}