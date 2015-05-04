#include "Timer.h"

Timer::Timer (): startTicks(0), pausedTicks(0), isStarted(false), isPaused(false) {

}


Timer::~Timer () {

}

void Timer::Start () {
	isStarted = true;
	isPaused = false;

	startTicks = SDL_GetTicks ();
	pausedTicks = 0;
}

void Timer::Stop () {
	isStarted = false;
	isPaused = false;

	startTicks = 0;
	pausedTicks = 0;
}

void Timer::Pause() {
	if (isStarted && !isPaused) {
		isPaused = true;
		pausedTicks = SDL_GetTicks () - startTicks;
		startTicks = 0;
	}
}

void Timer::Unpause () {
	if (isStarted && isPaused) {
		isPaused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 Timer::GetTicks () {
	Uint32 time = 0;

	if (isStarted) {
		if (isPaused) time = pausedTicks;
		else time = SDL_GetTicks () - startTicks;
	}
	return time;
}