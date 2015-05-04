#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
	Timer ();
	~Timer ();

	void Start ();
	void Stop ();
	void Pause ();
	void Unpause ();

	Uint32 GetTicks ();

	bool IsStarted () { return isStarted; }
	bool IsPaused () { return isStarted && isPaused; }

private:
	Uint32 startTicks;
	Uint32 pausedTicks;

	bool isStarted;
	bool isPaused;
};
#endif //TIMER_H