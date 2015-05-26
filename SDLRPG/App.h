#ifndef APP_H
#define APP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GameState.h"

#include "GameObjectManager.h"
#include "TextureManager.h"
#include "LevelManager.h"

#include "Timer.h"
#include "Window.h"
#include "Camera.h"

#include "Level.h"

class App {

public:
	static App* GetInst ();
	Window* GetWindow() { return &window; }
	GameObjectManager* GetGOManager() { return &goManager; }
	TextureManager* GetTextureManager () { return &textureManager; }
	LevelManager* GetLevelManager () { return &levelManager; }
	Level* GetCurrentLevel () { return currentLevel; }
	Camera* MainCamera () { return &mainCam; }
	
	void Init();
	
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
	Camera mainCam;

	GameObjectManager goManager;
	TextureManager textureManager;
	LevelManager levelManager;

	Level* currentLevel;

	const Uint8* keyStates;

	int windowWidth;
	int windowHeight;

	Timer timeSinceStart;
	Timer deltaTimer;
	float dt;
};

bool CheckCollision (SDL_Rect& a, SDL_Rect& b);
#endif //APP_H