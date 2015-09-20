#include "Level.h"

#include <algorithm>

#include "Tile.h"

Level::Level (int w, int h, int tileSize, const std::string& name) {
	this->name = name;
	this->tileSize = tileSize;
	Resize (w, h);
}


Level::~Level () {
	FreeLevel ();
}

void Level::Resize (int w, int h) {
	map.resize (w*h);

	// for (int i = 0; i < w; ++i) {
	// 	map.at (i).resize (h, 0);
	// }

	width = w;
	height = h;
}

void Level::AddTile (int x, int y, Tile* tile) {
	map[x+y*width] = tile;
}

Tile* Level::GetTile (int x, int y) {
	return map[x+y*width];
}

void Level::Draw () {
	Tile* tile;

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			tile = map[i+j*width];
			tile->Draw ();
		}
	}
}

void Level::FreeLevel () {
	for (size_t i = 0; i < map.size (); ++i) {
		// for (size_t j = 0; j < map[i].size (); ++j) {
			delete map[i];
		// }
	}
}