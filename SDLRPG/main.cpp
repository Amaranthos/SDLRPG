#include <SDL.h>

#include <iostream>
#include "App.h"

int main(int argc, char* argv[]) {

	App::GetInst ()->Init ();

	std::cin.get ();
	return 0;
}