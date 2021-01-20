#include "Grid.h"
#include "ScenceManager.h"

Grid::Grid(int mapwidth, int mapheight)
{//check
	maxXCells = mapwidth / CELL_WIDTH;
	maxYCells = mapheight / CELL_HEIGHT;

	for (int y = 0; y <= maxYCells; y++)
	{
		auto row = std::vector<Cell*>();

		for (int x = 0; x <= maxXCells; ++x)
		{
			row.push_back(new Cell(x, y));
		}

		cells.push_back(row);
	}

	this->camera = ScenceManager::GetInstance()->getCurrentScence()->getCamera();
}

Grid::~Grid()
{//check
}

void Grid::Update()
{
	getActiveCell();

	UpdateGridObjects();
}

void Grid::AddObject(GameObject* object)
{
	throw(OSS_UNIMPLEMENTED);
}

void Grid::AddObject(GameObject* object, int cellx, int celly, int spanx, int spany)
{
	throw(OSS_UNIMPLEMENTED);
}

Cell* Grid::getCell(int x, int y)
{
	return nullptr;
}

Cell* Grid::getCellbyObjPosition(float x, float y)
{
	int cellX = (int)(x / CELL_WIDTH);
	int cellY = (int)(y / CELL_HEIGHT);

	return getCell(cellX, cellY);
}

std::vector<GameObject*> Grid::getActiveGameObject()
{
	std::vector<GameObject*> coObject;

	for (size_t i = 0; i < activecells.size(); i++)
	{
		auto x = activecells[i]->getCellObject();

		auto o = x.begin();
		while (o != x.end())
		{
			if (dynamic_cast<LPGAMEOBJECT>(*o))
				coObject.push_back(*o);
			//UpdateActiveObjects(*o);
			o++;
		}
	}

	return coObject;
}

void Grid::UpdateActiveCell()
{
}

void Grid::UpdateGridObjects()
{
	std::vector<LPGAMEOBJECT> gridObjects = getActiveGameObject();

	auto o = gridObjects.begin();
	while (o != gridObjects.end())
	{
		UpdateGridObjectpos(*o);
		++o;
	}
}

void Grid::UpdateGridObjectpos(GameObject* obj)
{

	Cell* newCell = getCell(obj->getX(), obj->getY());
	if (newCell != obj->getOnwerCell())
	{
		obj->getOnwerCell()->RemoveObject(obj);
		newCell->AddObject(obj);
		obj->setOwnerCell(newCell);
	}
}

void Grid::getActiveCell()
{
	activecells.clear();

	int startX = (int)(camera->getCameraPositionX() / CELL_WIDTH);
	int endX = (int)((camera->getCameraPositionX() + WINDOW_WIDTH) / CELL_WIDTH);
	int startY = (int)(camera->getCameraPositionY() / CELL_HEIGHT);
	int endY = (int)((camera->getCameraPositionY() + WINDOW_HEIGHT) / CELL_HEIGHT);

	for (int i = startX; i <= endX; ++i)
	{
		if (i<0 || i>= maxXCells) continue;

		for (int j = startY; j <= endY; ++j)
		{
			if (j<0 || j > maxYCells) continue;

			activecells.push_back(cells[j][i]);
		}
	}
}
