#ifndef TILE_H
#define TILE_H

#include "Texture.h"
#include "TileType.h"
#include "Vec2.h"

class Tile {
public:
	Tile (SDL_Rect clip, int tileSize, TileType type, std::string& const image);
	~Tile ();

	void Draw ();

	void SetPos (Vec2& pos);

	int GetTileSize () const { return tileSize; }
	Vec2* GetTile () { return &pos; }
	SDL_Rect* GetClip () { return &clip; }
	TileType Type () const { return type; }
private:
	Texture* texture;

	int tileSize;

	Vec2 pos;

	SDL_Rect clip;
	TileType type;
};
#endif //TILE_H