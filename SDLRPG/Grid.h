#ifndef GRID_H
#define GRID_H

#include <vector>

#include "Vec2.h"

class GameObject;

struct ObjectHolder {
public:
	GameObject* go;
	Vec2 index;
};


class Grid {
public:
	typedef std::vector<std::vector<std::vector<GameObject*>>> Container;

	Grid (int cellSize);
	~Grid ();

	void Insert (GameObject* go);
	void Remove (GameObject* go);
	void Update (GameObject* go);

	std::vector<GameObject*> GetNeightbours (GameObject* go);

	void Clear ();

	int& getCellSize () { return cellSize; }
private:

	Container grid;
	int cellSize;
};
#endif //GRID_H