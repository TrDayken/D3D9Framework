#include "Grid.h"
#include "ScenceManager.h"

Grid::Grid(int mapwidth, int mapheight)
{
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
{
}

void Grid::Update()
{
	getActiveCell();

	UpdateGridObjects();
}

void Grid::AddObject(GameObject* object)
{
	Cell* cell = getCellbyObjPosition(object->getX(), object->getY());
	cell->AddObject(object);
	object->setOwnerCell(cell);
}

void Grid::AddObject(GameObject* object, int cellx, int celly)
{
	Cell* cell = this->cells[celly][cellx];
	cell->AddObject(object);
	object->setOwnerCell(cell);
}

void Grid::RemoveObject(GameObject* obj)
{
	Cell* cell = getCellbyObjPosition(obj->getX(), obj->getY());
	cell->RemoveObject(obj);
}

Cell* Grid::getCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= maxXCells) 
		x = maxXCells;

	if (y < 0) y = 0;
	if (y >= maxYCells) 
		y = maxYCells;

	return cells[y][x];
}

Cell* Grid::getCellbyObjPosition(float x, float y)
{
	int cellX = (int)(x / CELL_WIDTH);
	int cellY = (int)(y / CELL_HEIGHT);

	return getCell(cellX, cellY);
}

std::vector<GameObject*> Grid::getActiveGameObject()
{

	std::unordered_set<GameObject* > coObject;

	for (size_t i = 0; i < activecells.size(); i++)
	{
		auto x = activecells[i]->getCellObject();

		auto o = x.begin();
		while (o != x.end())
		{

			coObject.insert(*o);
			o++;
		}
	}

	std::vector<GameObject*> returned;

	returned.insert(returned.end(), coObject.begin(), coObject.end());

	return returned;
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

	Cell* newCell = getCellbyObjPosition(obj->getX(), obj->getY());
	if (newCell != obj->getOnwerCell())
	{
		obj->getOnwerCell()->RemoveObject(obj);
		newCell->AddObject(obj);
		obj->setOwnerCell(newCell);
	}
}

void Grid::DistributeGrid(std::vector<GameObject*> objects, std::string gridfilepath)
{
	TiXmlDocument doc(gridfilepath.c_str());


	if (!doc.LoadFile())
	{
		printf("%s", doc.ErrorDesc());
	}
	else
	{
		TiXmlElement* root = doc.RootElement();

		for (TiXmlElement* group = root->FirstChildElement("group"); group != NULL; group = group->NextSiblingElement("group"))
		{
			int id; 

			group->QueryIntAttribute("id", &id);

			for (TiXmlElement* object = group->FirstChildElement("object"); object != NULL; object = object->NextSiblingElement("object"))
			{
				int objid, cellx, celly, spanx, spany;
				
				object->QueryIntAttribute("id", &objid);
				object->QueryIntAttribute("cellx", &cellx);
				object->QueryIntAttribute("celly", &celly);
				object->QueryIntAttribute("spanx", &spanx);
				object->QueryIntAttribute("spany", &spany);

				GameObject* obj = NULL;
				for (int i = 0; i < objects.size(); i++)
				{
					int u = objects[i]->getID();
					if (objects[i]->getID() == objid)
					{
						obj = objects[i];

						for (int m = 0; m < spany; m++)
						{
							for (int n = 0; n < spanx; n++)
							{
								this->AddObject(obj, cellx + n, celly + m);
							}
						}

						continue;
					}
				}


			}
		}

		DebugOut(L"[INFO] Read file complete");
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
