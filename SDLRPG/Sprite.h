#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include "Texture.h"
#include "App.h"

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void LoadSprite(std::string path);

	Texture* GetTexture() { return texture; }

private:
	Texture* texture;
};
#endif SPRITE_H