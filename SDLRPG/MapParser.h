#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <string>
#include "Level.h"

class MapParser {
public:
	MapParser();
	~MapParser();

	Level LoadLevelFromFile (const std::string& path);
};

#endif