#ifndef APP_H
#define APP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GameState.h"
#include "Window.h"

class App {

public:
	static App* GetInst ();
	Window* GetWindow() { return &window; }
	
	void Init();
	
	const Uint8* KeyStates () { return keyStates; }

private:
	App ();
	~App ();

	bool InitSDL();
	void Update();
	bool IsExiting();
	void Close();

	static App* inst;
	Window window;
	GameState appState;

	const Uint8* keyStates;

	int windowWidth;
	int windowHeight;
};

#endif //APP_H