#include "GameObjectManager.h"

GameObjectManager::GameObjectManager () {

}


GameObjectManager::~GameObjectManager () {
	std::f
}

void GameObjectManager::Add (std::string name, GameObject* go) {
	gameObjects.insert (std::pair<std::string, GameObject*> (name, go));
}

