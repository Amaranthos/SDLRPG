#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <string>
#include <map>
#include <vector>

#include "TileType.h"
#include "Level.h"

class Tile;

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
		void operator() (const std::pair<std::string, Level*> &p) const {
			delete p.second;
		}
	};

	struct TileDeallocator {
		void operator() (const Tile* p) const {
			delete p;
		}
	};
};
#endif //LEVELMANAGER_H