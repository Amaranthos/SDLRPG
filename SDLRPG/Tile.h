#ifndef TILE_H
#define TILE_H

#include "Texture.h"

class Tile {
public:
	Tile (int x, int y, int w, int h, int type);
	~Tile ();

	void Draw ();

	SDL_Rect* GetTile () { return &tile; }
	int Type () const { return type; }
private:
	Texture* texture;

	SDL_Rect tile;
	int type;
};
#endif //TILE_H