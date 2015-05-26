#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

class Tile;

class Level {
public:
	Level (int w, int h, int tileSize, const std::string& name);
	~Level ();

	void FreeLevel ();

	void AddTile (int x, int y, Tile* tile);
	Tile* GetTile (int x, int y);

	void Draw ();

	int Width () const { return width * tileSize; }
	int Height () const { return height * tileSize; }

private:
	void Resize (int w, int h);

	std::vector<std::vector<Tile*>> map;

	int width;
	int height;
	int tileSize;

	std::string name;
};
#endif //LEVEL_H