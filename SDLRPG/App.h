#ifndef APP_H
#define APP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GameState.h"
#include "Timer.h"
#include "GameObjectManager.h"
#include "Window.h"
#include "Camera.h"

class App {

public:
	static App* GetInst ();
	Window* GetWindow() { return &window; }
	GameObjectManager* GetGOManager() { return &goManager; }
	Camera* MainCamera () { return &mainCam; }
	
	void Init();
	
	const static int levelWidth = 1280;
	const static int levelHeight = 960;

	const Uint8* KeyStates () const { return keyStates; }
	Uint32 TimeSinceStart () { return timeSinceStart.GetTicks (); }
	float DeltaTime () const { return dt; }
	
	int WindowWidth () const { return windowWidth; }
	int WindowHeight () const { return windowHeight; }
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
	GameObjectManager goManager;
	Camera mainCam;

	const Uint8* keyStates;

	int windowWidth;
	int windowHeight;

	Timer timeSinceStart;
	Timer deltaTimer;
	float dt;
};

#endif //APP_H