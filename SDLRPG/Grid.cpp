#include "Grid.h"

#include "App.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"
#include "ComponentID.h"

Grid::Grid (int cellSize): cellSize(cellSize) {
	grid.resize (App::GetInst ()->GetCurrentLevel ()->Width ());

	for (int x = 0; x < grid.size (); ++x)
		grid[x].resize (App::GetInst ()->GetCurrentLevel ()->Height ());
}


Grid::~Grid () {
	Clear ();
}

void Grid::Insert (GameObject* go) {
	Vec2 pos = (go->GetComponent<Transform>(ComponentID::Transform)->position);
	pos.x /= cellSize;
	pos.y /= cellSize;

	grid[pos.x][pos.y].push_back (go);
}

void Grid::Remove (GameObject* go) {
	Vec2 pos = (go->GetComponent<Transform> (ComponentID::Transform)->position);
	pos.x /= cellSize;
	pos.y /= cellSize;

	auto loc = std::find (grid[pos.x][pos.y].begin (), grid[pos.x][pos.y].end (), go);

	if (loc != grid[pos.x][pos.y].end ()) {
		*loc = grid[pos.x][pos.y].back ();
		grid[pos.x][pos.y].pop_back ();
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
		if (i + x > 0 && i + x < grid.size())
			for (int j = -range; j <= range; j++)
				if (j + y > 0 && j + y < grid[i].size())
					res.insert (res.end (), grid[i + x][j + y].begin (), grid[i + x][j + y].end ());
	
	return res;
}

void Grid::Clear () {
	for (int i = 0; i < grid.size (); ++i)
		for (int j = 0; j < grid[i].size (); ++j)
			grid[i][j].clear ();
}
