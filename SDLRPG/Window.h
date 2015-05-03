#ifndef WINDOW_H
#define WINDOW_H

#include <sstream>

#include <SDL.h>

#include "Colour.h"

class Window {
public:
	Window();
	~Window();

	bool Init (int width, int height, const std::string& name, const Colour clear = Colour(255, 255, 255, 255));

	void HandleEvent(SDL_Event& event);
	void Clear(Colour clear = Colour(255, 255, 255, 255));
	void Render();

	void Focus();

	void Free();

	//Getters and setters
	int Width() const { return width; }
	int Height() const { return height; }
	SDL_Renderer* Renderer() const{ return renderer; }
	SDL_Window* GetWindow() const{ return window; }
	bool HasMouseFocus() { return mouseFocus; }
	bool HasKeyboard() { return keyboardFocus; }
	bool IsMinimized() { return minimized; }
	bool IsShown() { return shown; }
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowID;

	int width;
	int height;

	bool mouseFocus;
	bool keyboardFocus;
	bool fullscreen;
	bool minimized;
	bool shown;
};

#endif //WINDOW_H
