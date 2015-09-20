#include "GameObjectManager.h"

#include <algorithm>

#include "GameObject.h"
#include "Grid.h"
#include "Component.h"
#include "Transform.h"

GameObjectManager::GameObjectManager () {

}


GameObjectManager::~GameObjectManager () {
	Clear ();
}

void GameObjectManager::Clear () {
	std::for_each (gameObjects.begin (), gameObjects.end (), GameObjectDeallocator ());
}

void GameObjectManager::Add (std::string name, GameObject* go) {
	gameObjects.insert (std::pair<std::string, GameObject*> (name, go));
	grid->Insert (go);
}

void GameObjectManager::Remove (std::string name) {
	std::map<std::string, GameObject*>::iterator results = gameObjects.find (name);
	
	if (results != gameObjects.end ()) {
		grid->Remove (results->second);
		delete results->second;
		gameObjects.erase (results);
	}
}

GameObject* GameObjectManager::Find (std::string name) const {
	std::map<std::string, GameObject*>::const_iterator result = gameObjects.find (name);
	if (result == gameObjects.end ()) return nullptr;
	return result->second;
}

void GameObjectManager::LoadLevel (int cellSize, int width, int height) {
	Clear ();

	if (grid) {
		delete grid;
		grid = nullptr;
	}

	grid = new Grid (cellSize, width, height);
}

void GameObjectManager::UpdateAll () {
	std::map<std::string, GameObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end ()) {
		itr->second->Update ();

		int i = grid->Index (itr->second);
		Vec2 pos = itr->second->GetComponent<Transform> (ComponentID::Transform)->position;

		int x = static_cast<int>(pos.x) / grid->CellSize ();
		int y = static_cast<int>(pos.y) / grid->CellSize ();

		if (i != x+y*grid->Width())
			grid->Update (itr->second);

		itr++;
	}
}

void GameObjectManager::GameObjectDeallocator::operator () (const std::pair<std::string, GameObject*> &p) const {
	delete p.second;
}