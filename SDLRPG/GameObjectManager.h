#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <string>
#include <map>

class GameObject;

class GameObjectManager {
public:
	GameObjectManager ();
	~GameObjectManager ();

	void Add (std::string name, GameObject* go);
	void Remove (std::string name);
	GameObject* Find (std::string name) const;

	void UpdateAll ();

	int Count () const { return count; }

private:
	std::map<std::string, GameObject*> gameObjects;
	int count;

	struct GameObjectDeallocator{
		void operator () (const std::pair<std::string, GameObject*> &p) const {
			delete p.second;
		}
	};
};
#endif //GAMEOBJECTMANAGER_H