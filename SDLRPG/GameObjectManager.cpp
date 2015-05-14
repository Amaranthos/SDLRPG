#include "GameObjectManager.h"

#include <algorithm>

#include "GameObject.h"

GameObjectManager::GameObjectManager () {

}


GameObjectManager::~GameObjectManager () {
	std::for_each (gameObjects.begin (), gameObjects.end (), GameObjectDeallocator ());
}

void GameObjectManager::Add (std::string name, GameObject* go) {
	gameObjects.insert (std::pair<std::string, GameObject*> (name, go));
}

void GameObjectManager::Remove (std::string name) {
	std::map<std::string, GameObject*>::iterator results = gameObjects.find (name);

	if (results != gameObjects.end ()) {
		delete results->second;
		gameObjects.erase (results);
	}
}

GameObject* GameObjectManager::Find (std::string name) const {
	std::map<std::string, GameObject*>::const_iterator result = gameObjects.find (name);
	if (result == gameObjects.end ()) return nullptr;
	return result->second;
}

void GameObjectManager::UpdateAll () {
	std::map<std::string, GameObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end ()) {
		itr->second->Update ();
		itr++;
	}
}