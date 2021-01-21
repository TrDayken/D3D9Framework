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

	int maxXCells, maxYCells;

	// available cells
	std::vector <std::vector<Cell*>> cells;

	// current using cells;
	std::vector <Cell*> activecells;

public:
	//init passing mapwidth , and map height to calculate cells
	Grid(int mapwidth, int mapheight);
	~Grid();

	// update grid
	void Update();

	//add object to grid
	void AddObject(GameObject* object);

	void AddObject(GameObject* object, int cellx, int celly);

	void RemoveObject(GameObject* obj);

	//use this to get specific cell in grid
	Cell* getCell(int x, int y);

	Cell* getCellbyObjPosition(float x, float y);

	std::vector<GameObject*> getActiveGameObject();

	void getActiveCell();
	void UpdateActiveCell();

	void UpdateGridObjects();

	void UpdateGridObjectpos(GameObject* obj);

	void DistributeGrid(std::vector<GameObject*> objects, std::string gridfilepath);

};

#endif // !__GRID_H__