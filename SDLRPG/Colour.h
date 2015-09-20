#ifndef COLOUR_H
#define COLOUR_H

#include <SDL.h>

class Colour {
public:
	Colour (Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	Colour (Uint8 r, Uint8 g, Uint8 b);
	~Colour ();

	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;
};

#endif //COLOUR_H