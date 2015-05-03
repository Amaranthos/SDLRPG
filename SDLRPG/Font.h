#ifndef FONT_H
#define FONT_H

#include <string>

#include <SDL_ttf.h>

class Font {
public:
	Font ();
	~Font ();
	
	void LoadFont (std::string path, int fontSize);

	TTF_Font* GetFont () const{ return font; }

private:
	TTF_Font* font;
};

#endif //FONT_H