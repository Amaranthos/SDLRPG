#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Colour.h"

class Window;
class Font;
struct Vec2;

class Texture {
public:
	Texture ();
	~Texture ();

	bool LoadFromFile (const std::string& path, Window* window, Colour transparentKey = Colour(255, 0, 255, 255));

	#ifdef _SDL_TTF_H
	bool LoadFromRenderedText (const std::string& text, Colour textColour, Font font, Window* window);
	#endif

	void Render (int posX, int posY, Window* window, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* centre = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Render (Vec2* pos, Window* window, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* centre = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void SetColourTint (Colour colour);
	void SetAlpha (Uint8 alpha);
	void SetBlendMode (SDL_BlendMode mode);

	void SetAsRenderTarget (Window* window);

	bool CreateBlank (int width, int height, Window* window, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);
	bool LockTexture ();
	bool UnlockTexture ();
	Uint32 GetPixels32 (unsigned int x, unsigned int y);
	void CopyPixels (void* pixels);

	void Free ();

	int Width () const { return width; }
	int Height () const { return height; }
	void* Pixels () const { return pixels; }
	int Pitch () const { return pitch; }

private:
	SDL_Texture* texture;
	void* pixels;
	int pitch;

	unsigned int width, height;
};

#endif //TEXTURE_H