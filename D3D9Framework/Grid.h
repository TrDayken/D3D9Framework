#ifndef __GRID_H__
#define __GRID_H__

#include <vector>

#include "Cell.h"
#include "Global_Variable.h"
#include "Camera.h"
#include "GameObject.h"

class Grid
{
private:
	Camera* camera;

	std::vector <std::vector<Cell*>> cells;
	std::vector <Cell*> activecells;

public:
	Grid(int mapwidth, int mapheight);
	~Grid();

	void Update();

	void AddObject(GameObject* object);

	//use this to get specific cell in grid
	Cell* getCell(int x, int y);

	std::vector<GameObject> getActiveGameObject();

	std::vector<Cell*> getActiveCell();
};

#endif // !__GRID_H__