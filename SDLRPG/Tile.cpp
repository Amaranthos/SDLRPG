#include "Tile.h"

#include "App.h"

Tile::Tile (SDL_Rect clip, int tileSize, TileType type, std::string& const image) {
	this->clip = clip;
	this->type = type;
	this->tileSize = tileSize;
	texture = new Texture ();
	texture = App::GetInst()->GetTextureManager()->GetTexture(image);
}

Tile::~Tile () {
	texture->Free ();
}

void Tile::SetPos (Vec2& pos) {
	this->pos = pos;
}

void Tile::Draw () {
	if (CheckCollision (SDL_Rect{ (int)pos.x, (int)pos.y, tileSize, tileSize }, *App::GetInst ()->MainCamera ()->View ()))
		texture->Render (pos.x - App::GetInst ()->MainCamera ()->View ()->x, pos.y - App::GetInst ()->MainCamera ()->View ()->y, App::GetInst ()->GetWindow (), &clip);
}