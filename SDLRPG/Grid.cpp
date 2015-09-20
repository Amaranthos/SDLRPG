#include "Grid.h"

#include "App.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"
#include "ComponentID.h"

#include <algorithm>

Grid::Grid (int cellSize): cellSize(cellSize) {
	width = App::GetInst ()->GetCurrentLevel ()->Width ();
	grid.resize (width * App::GetInst ()->GetCurrentLevel ()->Height ());

	// for (size_t x = 0; x < grid.size (); ++x)
	// 	grid[x].resize (App::GetInst ()->GetCurrentLevel ()->Height ());
}


Grid::~Grid () {
	Clear ();
}

void Grid::Insert (GameObject* go) {
	Vec2 pos = (go->GetComponent<Transform>(ComponentID::Transform)->position);
	pos.x /= cellSize;
	pos.y /= cellSize;

	grid[pos.x+pos.y*width].push_back (go);
}

void Grid::Remove (GameObject* go) {
	Vec2 pos = (go->GetComponent<Transform> (ComponentID::Transform)->position);
	pos.x /= cellSize;
	pos.y /= cellSize;

	auto loc = std::find (grid[pos.x+pos.y*width].begin (), grid[pos.x+pos.y*width].end (), go);

	if (loc != grid[pos.x+pos.y*width].end ()) {
		*loc = grid[pos.x+pos.y*width].back ();
		grid[pos.x+pos.y*width].pop_back ();
	}
}

void Grid::Update (GameObject* go) {
	Remove (go);
	Insert (go);
}

std::vector<GameObject*> Grid::GetNeightbours (GameObject* go) {
	std::vector<GameObject*> res;
	int range = 1;

	if (go->Height () >= go->Width ())
		range = go->Height() / cellSize;
	else
		range = go->Width() / cellSize;

	int x = 0;
	int y = 0;

	for (int i = -range; i <= range; ++i)
		if (i + x > 0 && i + x < width)
			for (int j = -range; j <= range; j++)
				if (j + y > 0 && j + y < (int)grid.size()/width)
					res.insert(res.end(), grid[i + x+(j+y)*width].begin(), grid[i + x+(j+y)*width].end());
	
	return res;
}

void Grid::Clear () {
	for (size_t i = 0; i < grid.size(); ++i)
		// for (size_t j = 0; j < grid[i].size (); ++j)
			grid[i].clear ();
}
