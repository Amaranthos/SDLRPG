#include "Colour.h"

Colour::Colour (Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

Colour::Colour (Uint8 r, Uint8 g, Uint8 b): alpha(255) {
	red = r;
	green = g;
	blue = b;
}


Colour::~Colour () {

}
