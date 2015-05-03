#include "App.h"

App* App::inst = nullptr;

App::App () :windowWidth (960), windowHeight (720), appState(Uninitalized), window(Window()) {

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

			if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				printf("Warning: SDL_Mixer could not init! SDL_Mixer Error: %s\n", Mix_GetError());
				success = false;
			}
			else printf ("Success: SDL_Mixer initialized!\n");
		}
	}
	return success;
}

void App::Update () {
	SDL_Event event;

	keyStates = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent (&event) != 0) {
		switch (appState) {
		case GameState::Playing:
			if (event.type == SDL_QUIT)
				appState = Exiting;

			window.HandleEvent (event);
			break;		
		}
	}

	window.Clear ();

	

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