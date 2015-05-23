#include "Tile.h"

#include "App.h"

Tile::Tile (int x, int y, int w, int h, int type) {
	texture = new Texture ();
	tile.x = x;
	tile.y = y;
	tile.w = w;
	tile.h = h;
	this->type = type;
	texture = App::GetInst()->GetTextureManager()->GetTexture("img/tile.png");
}


Tile::~Tile () {
	texture->Free ();
}

void Tile::Draw () {
	if (CheckCollision (tile, *App::GetInst ()->MainCamera ()->View ())) 
		texture->Render (tile.x - App::GetInst ()->MainCamera ()->View ()->x, tile.y - App::GetInst ()->MainCamera ()->View ()->y, App::GetInst ()->GetWindow ());
}