#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

class Tile;

class Level {
public:
	Level (int w, int h);
	~Level ();

	void LoadLevel ();
	void FreeLevel ();

	void AddTile (int x, int y, Tile* tile);
	Tile* GetTile (int x, int y);

	void Draw ();

	int Width () const { return width; }
	int Height () const { return height; }

private:
	void Resize (int w, int h);

	std::vector<std::vector<Tile*>> map;

	int width;
	int height;
};
#endif //LEVEL_H