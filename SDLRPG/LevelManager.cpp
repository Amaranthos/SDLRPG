#include "LevelManager.h"

#include <algorithm>
#include <fstream>
#include <string>

#include "rapidxml\rapidxml.hpp"

#include "App.h"
#include "Level.h"
#include "Tile.h"

LevelManager::LevelManager () {
	std::for_each (levels.begin(), levels.end(), LevelDeallocator());
	std::for_each (tileMasterList.begin (), tileMasterList.end (), TileDeallocator ());
}


LevelManager::~LevelManager () {

}

Level* LevelManager::GetLevel (const std::string& path) {
	std::map<std::string, Level*>::iterator itr = levels.find (path);

	if (itr == levels.end ()) return LoadLevel (path);
	return itr->second;
}

Tile LevelManager::GetTile (TileType index) {
	return *tileMasterList[index];	
}

int LevelManager::LoadTileSet (const std::string& path) {
	//Clear old 
	std::for_each (tileMasterList.begin (), tileMasterList.end (), TileDeallocator ());
	int tileSize = 0;

	//Load file
	std::ifstream input (path);

	//Ensure it opened
	if (!input) printf ("Warning! Could not open file: %s\n", path.c_str ());

	//Get the contents
	std::string fileContents;
	std::string line;
	while (std::getline (input, line)) fileContents += line;

	//Convert to rapidxml format
	std::vector<char> data = std::vector<char> (fileContents.begin (), fileContents.end ());
	data.push_back ('\0');

	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes> (&data[0]);

	rapidxml::xml_node<>* root = doc.first_node ();

	rapidxml::xml_node<>* file = root->first_node ("image");

	while (file) {
		std::string path = file->first_attribute ("path")->value ();

		App::GetInst ()->GetTextureManager ()->GetTexture (path);

		tileSize = atoi (file->first_attribute ("tilesize")->value ());

		rapidxml::xml_node<>* tile = file->first_node ("tile");

		while (tile) {
			int index = atoi (tile->first_attribute ("index")->value ());
			int x = atoi (tile->first_attribute ("x")->value ());
			int y = atoi (tile->first_attribute ("y")->value ());
			//int cost = atoi (tile->first_attribute ("cost")->value ());

			Tile* temp = new Tile (SDL_Rect{ x * tileSize, y * tileSize, tileSize, tileSize }, tileSize, (TileType)index, path);
			tileMasterList.push_back (temp);

			tile = tile->next_sibling ();
		}

		file = file->next_sibling ();
	}
	return tileSize;
}

Level* LevelManager::LoadLevel (const std::string& path) {
	
	//Load file
	std::ifstream input (path);

	//Ensure it opened
	if (!input) {
		printf ("Warning! Could not open file: %s\n", path.c_str ());
		return nullptr;
	}

	//Get the contents
	std::string fileContents;
	std::string line;
	while (std::getline (input, line)) fileContents += line;

	//Convert to rapidxml format
	std::vector<char> data = std::vector<char> (fileContents.begin (), fileContents.end ());
	data.push_back ('\0');

	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes> (&data[0]);

	rapidxml::xml_node<>* root = doc.first_node ();

	int width = atoi (root->first_attribute ("width")->value ());
	int height = atoi (root->first_attribute ("height")->value ());

	
	rapidxml::xml_node<>* tileset = root->first_node ("tileset");

	

	Level* level = new Level (width, height, LoadTileSet (tileset->first_attribute ("path")->value ()), root->first_attribute ("name")->value ());

	std::string tiles = root->first_node ("tiles")->value();
	
	int x = 0;
	int y = 0;

	if (!level) {
		printf ("Warning! Could not create level\n");
		return nullptr;
	}

	for (std::string::iterator itr = tiles.begin (); itr != tiles.end (); ++itr) {
		if (*itr != ' ' && *itr != '\n' && *itr != '\r' && *itr != '\t') {

			Tile* tile = new Tile (GetTile ((TileType)std::atoi (&(*itr))));
				
			tile->SetPos(Vec2{(float) x * tile->GetTileSize(), (float) y * tile->GetTileSize() });
			level->AddTile (x, y, tile);

			++x;
			if (x % width == 0) {
				x = 0; 
				++y;
			}
		}
	}

	App::GetInst ()->GetGOManager ()->LoadLevel (level->TileSize (), level->NumTilesX (), level->NumTilesY ());

	printf ("Success: Loaded level: %s!\n", path.c_str ());
	return level;
}

void LevelManager::LevelDeallocator::operator() (const std::pair<std::string, Level*> &p) const {
	delete p.second;
}

void LevelManager::TileDeallocator::operator () (const Tile* p) const {
	delete p;
}