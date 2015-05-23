#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <vector>

class Tile;

class MapParser {
public:
	MapParser ();
	~MapParser ();

	std::vector<std::vector<Tile*>> LoadLevelFromFile (std::string& const path);
};
#endif //MAPPARSER_H