#include "Grid.h"

#include "App.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"
#include "ComponentID.h"

Grid::Grid (int cellSize, int width, int height) : cellSize(cellSize), width(width), height(height) {
	grid.resize (width*height);
}


Grid::~Grid () {
	Clear ();
}

void Grid::Insert (GameObject* go) {
	Vec2 pos = (go->GetComponent<Transform>(ComponentID::Transform)->position);

	int x = static_cast<int>(pos.x) / cellSize;
	int y = static_cast<int>(pos.y) / cellSize;

	indexes.insert ({ go, x + y * width });

	grid[x + y * width].push_back (go);
}

void Grid::Remove (GameObject* go) {
	int index = -1;
	index = indexes.find (go)->second;

	if (index != -1) {
		auto loc = std::find (grid[index].begin (), grid[index].end (), go);

		if (loc != grid[index].end ()) {
			*loc = grid[index].back ();
			grid[index].pop_back ();
		}

		indexes.erase (indexes.find(go));
	}
}

void Grid::Update (GameObject* go) {
	Remove (go);
	Insert (go);
}

std::vector<GameObject*> Grid::GetNeightbours (GameObject* go) {
	std::vector<GameObject*> res;

	int index = -1;
	index = indexes.find (go)->second;

	if (index != -1) {
		int range = 1;

		if (go->Height () >= go->Width ())
			range = go->Height() / cellSize;
		else
			range = go->Width() / cellSize;

		for (int i = -range; i <= range; ++i)
				for (int j = -range; j <= range; j++)
					if (index + i + j * width > 0 && index + i + j * width < width*height)
						res.insert (res.end (), grid[index + i + j * width].begin (), grid[index + i + j * width].end ());
	
	}
	return res;
}

int Grid::Index (GameObject* go) {
	return indexes.find (go)->second;
}

void Grid::Clear () {
	for (size_t i = 0; i < grid.size (); ++i)
		for (size_t j = 0; j < grid[i].size (); ++j)
			grid[i + j * width].clear ();

	indexes.clear ();
}
