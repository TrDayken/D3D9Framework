#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x; 
	this->y = y;

	cellrect.top = x * CELL_WIDTH;
	cellrect.left = y * CELL_HEIGHT;
	cellrect.right = x * CELL_WIDTH + CELL_WIDTH;
	cellrect.bottom = y * CELL_HEIGHT + CELL_HEIGHT;
}

Cell::~Cell()
{
}

int Cell::getX()
{
	return this->x;
}

int Cell::getY()
{
	return this->y;
}

void Cell::AddObject(GameObject* obj)
{
	if (!(objects.find(obj) != objects.end()))
	{
		objects.insert(obj);
	}
}

void Cell::RemoveObject(GameObject* obj)
{
	if (objects.find(obj) != objects.end())
	{
		objects.erase(obj);
	}
}

std::unordered_set<GameObject*> Cell::getCellObject()
{
	return this->objects;
}
