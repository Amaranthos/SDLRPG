#ifndef GRID_H
#define GRID_H

#include <vector>
#include <unordered_map>

#include "Vec2.h"

class GameObject;

struct ObjectHolder {
public:
	GameObject* go;
	Vec2 index;
};


class Grid {
public:
	typedef std::vector<std::vector<GameObject*>> Container;

	Grid (int cellSize, int width, int height);
	~Grid ();

	void Insert (GameObject* go);
	void Remove (GameObject* go);
	void Update (GameObject* go);

	int Index (GameObject* go);

	std::vector<GameObject*> GetNeightbours (GameObject* go);

	void Clear ();

	int CellSize () const { return cellSize; }
	int Height () const { return height; }
	int Width () const { return width; }

private:

	Container grid;
	
	unsigned int cellSize, height, width;

	std::unordered_map<GameObject*, int> indexes;
};
#endif //GRID_H