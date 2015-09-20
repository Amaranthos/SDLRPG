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

	void operator=(const Sprite& item);

private:
	Texture* texture;
};
#endif //SPRITE_H