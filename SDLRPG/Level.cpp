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
	map.resize (w);

	for (size_t i = 0; i < w; ++i) {
		map.at (i).resize (h, 0);
	}

	width = w;
	height = h;
}

void Level::AddTile (int x, int y, Tile* tile) {
	map[x][y] = tile;
}

Tile* Level::GetTile (int x, int y) {
	return map[x][y];
}

void Level::Draw () {
	Tile* tile;

	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			tile = map[i][j];
			tile->Draw ();
		}
	}
}

void Level::FreeLevel () {
	for (size_t i = 0; i < map.size (); ++i) {
		for (size_t j = 0; j < map[i].size (); ++j) {
			delete map[i][j];
		}
	}
}