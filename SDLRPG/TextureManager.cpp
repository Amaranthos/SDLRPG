#include "TextureManager.h"

#include <algorithm>

#include "App.h"
#include "Texture.h"

TextureManager::TextureManager () {
}


TextureManager::~TextureManager () {
	std::for_each (textures.begin (), textures.end (), TextureDeallocator ());
}

Texture* TextureManager::GetTexture (std::string name) {
	std::map<std::string, Texture*>::iterator itr = textures.find (name);

	if (itr == textures.end ()) {
		Texture* texture = new Texture ();

		if (!texture->LoadFromFile (name, App::GetInst ()->GetWindow ())) {
			delete texture;
		}

		std::map<std::string, Texture*>::iterator res = textures.insert (std::pair<std::string, Texture*> (name, texture)).first;

		return texture;
	}
	else return itr->second;
}


void TextureManager::TextureDeallocator::operator() (const std::pair<std::string, Texture*>&p) const {
	delete p.second;
}