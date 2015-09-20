#include <SDL.h>

#include <iostream>
#include "App.h"

int main(int, char**) {

	App::GetInst ()->Init ();

	std::cin.get ();
	return 0;
}