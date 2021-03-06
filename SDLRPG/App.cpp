#include "App.h"

#include <iostream>

#include "PlayerController.h"
#include "Texture.h"

App* App::inst = nullptr;

App::App () : windowWidth (960), windowHeight (720),  appState(Uninitalized), mainCam(Camera(960, 720)), dt(0) {

}

App::~App () {
	Close ();
}

App* App::GetInst () {
	if (!inst) inst = new App ();
	return inst;
}

void App::Init () {
	if (appState != Uninitalized) {
		printf ("Warning: App already initalized!\n");
		return;
	}
	if (!InitSDL ()) return;

	appState = GameState::Playing;


	currentLevel = levelManager.GetLevel ("maps/testlevel.map");

	PlayerController* player = new PlayerController();
	goManager.Add ("Player", player);

	while (!IsExiting ())
		Update ();

	Close ();
}

bool App::InitSDL () {
	bool success = true;
 
	if (SDL_Init (SDL_INIT_EVERYTHING) < 0) {
		printf ("Warning: SDL could not init! SDL Srror: %s\n", SDL_GetError ());
		success = false;
	}
	else {
		printf ("Success: SDL initialized!\n");
		if (!SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "1")) printf ("Warning: Linear texture filtering not enabled!\n");

		if (!window.Init (windowWidth, windowHeight, "SDLRPG")) success = false;
		else {
			int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			if (!(IMG_Init (imgFlags) & imgFlags)) {
				printf ("SDL_Image could not init! SDL_Image Error: %s\n", IMG_GetError ());
				success = false;
			}
			else printf ("Success: SDL_Image initialized!\n");

			if (TTF_Init () == -1) {
				printf ("SDL_TTF could not init! SDL_TTF Error: %s\n", TTF_GetError ());
				success = false;
			}
			else printf ("Success: SDL_TTF initialized!\n");

			if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
				printf("Warning: SDL_Mixer could not init! SDL_Mixer Error: %s\n", Mix_GetError());
				success = false;
			}
			else printf ("Success: SDL_Mixer initialized!\n");
			timeSinceStart.Start ();
		}
	}
	return success;
}

void App::Update () {
	SDL_Event event;

	keyStates = SDL_GetKeyboardState(NULL);
	if (keyStates[SDL_SCANCODE_ESCAPE]) appState = Exiting;

	while (SDL_PollEvent (&event) != 0) {
		switch (appState) {
		case GameState::Playing:
			if (event.type == SDL_QUIT)
				appState = Exiting;

			window.HandleEvent (event);
			break;

		default:
			break;
		}
	}


	dt = deltaTimer.GetTicks () / 1000.0f;
	deltaTimer.Start ();

	window.Clear ();

	currentLevel->Draw ();
	goManager.UpdateAll ();

	window.Render ();
}

void App::Close () {
	window.Free ();

	Mix_Quit ();
	IMG_Quit ();
	TTF_Quit ();
	SDL_Quit ();
}

bool App::IsExiting () {
	return appState == Exiting;
}

bool CheckCollision (const SDL_Rect& a, const SDL_Rect& b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	//If none of the sides from A are outside B
	return true;
}