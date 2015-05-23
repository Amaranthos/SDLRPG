#include "Level.h"

#include "Tile.h"

Level::Level (int w, int h) {
	Resize (w, h);
	width = w;
	height = h;
}


Level::~Level () {
}

void Level::Resize (int w, int h) {
	map.resize (w);

	for (size_t i = 0; i < w; ++i) {
		map.at (i).resize (h, 0);
	}
}

void Level::AddTile (int x, int y, Tile* tile) {
	map[x][y] = tile;
}

Tile* Level::GetTile (int x, int y) {
	return map[x][y];
}

void Level::LoadLevel () {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			AddTile (i, j, new Tile (i* 64, j *64, 64, 64, 1));
		}
	}
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