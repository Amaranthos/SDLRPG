#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "Component.h"

class Texture;

class Sprite : public Component {
public:
	Sprite();
	~Sprite();

	void LoadSprite(const std::string& path);

	Texture* GetTexture() const { return texture; }

private:
	Texture* texture;
};
#endif