#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <string>
#include <map>

class GameObject;
class Grid;

class GameObjectManager {
public:
	GameObjectManager ();
	~GameObjectManager ();

	void Clear ();

	void Add (std::string name, GameObject* go);
	void Remove (std::string name);
	GameObject* Find (std::string name) const;

	void LoadLevel (int cellsize, int width, int height);

	void UpdateAll ();

	int Count () const { return count; }

private:
	std::map<std::string, GameObject*> gameObjects;
	Grid* grid;

	unsigned int count;

	struct GameObjectDeallocator{
		void operator () (const std::pair<std::string, GameObject*> &p) const;
	};
};
#endif //GAMEOBJECTMANAGER_H