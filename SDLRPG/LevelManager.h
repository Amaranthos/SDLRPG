#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <string>
#include <map>
#include <vector>

#include "TileType.h"

class Tile;
class Level;

class LevelManager {
public:
	LevelManager ();
	~LevelManager ();

	Level* GetLevel (const std::string& path);
	Tile GetTile (TileType index);

	int LoadTileSet (const std::string& path);

private:
	std::map <std::string, Level*> levels;
	std::vector<Tile*> tileMasterList;

	Level* LoadLevel (const std::string& path);

	struct LevelDeallocator {
		void operator() (const std::pair<std::string, Level*> &p) const;
	};

	struct TileDeallocator {
		void operator() (const Tile* p) const;
	};
};
#endif //LEVELMANAGER_H