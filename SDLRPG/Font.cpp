#include "Font.h"

#include <SDL_ttf.h>

Font::Font (): font(nullptr) {
	
}

Font::~Font () {
	delete font;
	font = nullptr;
}

void Font::LoadFont (std::string path, int fontSize) {
	font = TTF_OpenFont (path.c_str (), fontSize);

	if (font) printf ("Success: Loaded font %s\n!", path.c_str ());
	else printf ("Warning: Unable to load font %s! SDL_TTF Error: %s\n", path.c_str (), TTF_GetError ());
}