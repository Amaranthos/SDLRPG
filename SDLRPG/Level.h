#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

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

	int TileSize () const { return  tileSize; }
	int NumTilesX () const { return width; }
	int NumTilesY () const { return height; }

private:
	void Resize (int w, int h);

	std::vector<Tile*> map;

	unsigned int width, height, tileSize;

	std::string name;
};
#endif //LEVEL_H