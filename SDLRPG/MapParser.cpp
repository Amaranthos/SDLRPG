#include "MapParser.h"

#include <fstream>

#include "rapidxml\rapidxml.hpp"

#include "App.h"
#include "Tile.h"
#include "Level.h"

MapParser::MapParser () {

}


MapParser::~MapParser () {

}

Level MapParser::LoadLevelFromFile (std::string& const path) {
	//Load file
	std::ifstream input (path);

	//Ensure it opened
	if (!input) printf ("Warning! Could not open file: %s\n", path.c_str ());

	//Get the contents
	std::string fileContents;
	std::string line;
	while (std::getline (input, line))fileContents += line;

	//Convert to rapidxml format
	std::vector<char> data = std::vector<char> (fileContents.begin (), fileContents.end ());
	data.push_back ('\0');

	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes> (&data[0]);

	rapidxml::xml_node<>* root = doc.first_node ();

	std::string mapName = root->first_attribute("name")->value();
	int mapWidth = atoi (root->first_attribute ("width")->value ());
	int mapHeight = atoi (root->first_attribute ("height")->value ());

	std::string imagePath;
	Texture* tileset;
	int tileSize;

	rapidxml::xml_node<>* imageFile = root->first_node ("tileinfo");

	while (imageFile) {
		imagePath = imageFile->first_attribute ("path")->value ();
		tileset = App::GetInst ()->GetTextureManager ()->GetTexture (imagePath);

		tileSize = atoi(imageFile->first_attribute ("tilesize")->value ());

		rapidxml::xml_node<>* tile = imageFile->first_node ("tile");

		while (tile) {
			int index = atoi (tile->first_attribute ("index")->value ());
			int x = atoi (tile->first_attribute ("x")->value ());
			int y = atoi (tile->first_attribute ("y")->value ());
			int cost = atoi (tile->first_attribute ("cost")->value ());

		}
	}
}
