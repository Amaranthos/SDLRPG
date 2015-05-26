#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>

class Texture;

class TextureManager {
public:
	TextureManager ();
	~TextureManager ();

	Texture* GetTexture (std::string name);

private:
	std::map<std::string, Texture*> textures;

	struct TextureDeallocator {
		void operator() (const std::pair<std::string, Texture*>&p) const {
			delete p.second;
		}
	};
};
#endif //TEXTUREMANAGER_H