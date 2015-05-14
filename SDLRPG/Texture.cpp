#include "Texture.h"

#include "Window.h"
#include "Colour.h"
#include "Font.h"
#include "Vec2.h"

Texture::Texture () : width(0), height(0), texture(nullptr) {
	
}


Texture::~Texture () {
	Free ();
}

bool Texture::LoadFromFile (const std::string& path, Window* window, Colour transparentKey) {
	Free ();

	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load (path.c_str ());

	if (loadedSurface) {
		printf ("Success: Loaded image %s!\n", path.c_str ());

		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat (loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);

		if (formattedSurface) {
			newTexture = SDL_CreateTexture (window->Renderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);

			if (newTexture) {
				SDL_SetTextureBlendMode (newTexture, SDL_BLENDMODE_BLEND);

				SDL_LockTexture (newTexture, nullptr, &pixels, &pitch);
				memcpy (pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				width = formattedSurface->w;
				height = formattedSurface->h;

				Uint32* pixelsTemp = (Uint32*)pixels;
				int pixelCount = (pitch / 4) * height;

				Uint32 colorKey = SDL_MapRGB (formattedSurface->format, transparentKey.red, transparentKey.green, transparentKey.blue);
				Uint32 transparent = SDL_MapRGBA (formattedSurface->format, 255, 255, 255, 0);

				for (int i = 0; i < pixelCount; ++i)
					if (pixelsTemp[i] == colorKey)
						pixelsTemp[i] = transparent;

				SDL_UnlockTexture (newTexture);
				pixels = nullptr;
			}
			else printf ("Warning: Unable to create blank texture! SDL Error: %s\n", SDL_GetError());

			SDL_FreeSurface (formattedSurface);
		}
		else printf ("Warning: Unable to covert %S to display format! SDL_Image Error: %s\n", path.c_str (), SDL_GetError());

		SDL_FreeSurface (loadedSurface);
	}
	else printf ("Warning: Unable to load image %S! SDL_Image Error: %s\n", path.c_str (), IMG_GetError ());
	texture = newTexture;
	return !!texture;
}

#ifdef _SDL_TTF_H
bool Texture::LoadFromRenderedText (const std::string& text, Colour textColour, Font font, Window* window) {
	Free ();
	SDL_Color temp = { textColour.red, textColour.green, textColour.blue };
	SDL_Surface* textImage = TTF_RenderUTF8_Blended (font.GetFont (), text.c_str (), temp);

	if (textImage) {
		texture = SDL_CreateTextureFromSurface (window->Renderer (), textImage);

		if (texture) {
			width = textImage->w;
			height = textImage->h;
		}
		else printf ("Warning: Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError ());

		SDL_FreeSurface (textImage);
	}
	else printf ("Warning: Unable to render text! SDL_TTF Error: %s\n", TTF_GetError ());

	return !!texture;
}
#endif

void Texture::Render (int posX, int posY, Window* window, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { posX, posY, width, height };

	if (clip) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx (window->Renderer (), texture, clip, &renderQuad, angle, centre, flip);
}

void Texture::Render (Vec2* pos, Window* window, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { (int)pos->X(), (int)pos->Y(), width, height };

	if (clip) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx (window->Renderer (), texture, clip, &renderQuad, angle, centre, flip);
}

void Texture::SetColourTint (Colour colour) {
	SDL_SetTextureColorMod (texture, colour.red, colour.green, colour.blue);
}

void Texture::SetAlpha (Uint8 alpha) {
	SDL_SetTextureAlphaMod (texture, alpha);
}

void Texture::SetBlendMode (SDL_BlendMode mode) {
	SDL_SetTextureBlendMode (texture, mode);
}

bool Texture::LockTexture () {
	bool success = true;
	if (pixels) success = false;
	else
		if (SDL_LockTexture (texture, nullptr, &pixels, &pitch) != 0) success = false;
	return success;
}

bool Texture::UnlockTexture () {
	bool success = true;
	if (!pixels) success = false;
	else {
		SDL_UnlockTexture (texture);
		pixels = nullptr;
		pitch = 0;
	}
	return success;
}

Uint32 Texture::GetPixels32 (unsigned int x, unsigned int y) {
	Uint32* pixelsTemp = (Uint32*) pixels;
	return pixelsTemp[(y * (pitch / 4)) + x];
}

bool Texture::CreateBlank (int width, int height, Window* window, SDL_TextureAccess access) {
	texture = SDL_CreateTexture (window->Renderer (), SDL_PIXELFORMAT_RGBA8888, access, width, height);

	if (texture) {
		this->width = width;
		this->height = height;
	}
	else printf ("Warning: Unable to create blank texture! SDL Error: %s\n", SDL_GetError ());
	return !!texture;
}

void Texture::CopyPixels (void* pixels) {
	if (pixels) memcpy (this->pixels, pixels, pitch * height);
}

void Texture::SetAsRenderTarget (Window* window) {
	SDL_SetRenderTarget (window->Renderer (), texture);
}

void Texture::Free () {
	if (texture) {
		SDL_DestroyTexture (texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}
}