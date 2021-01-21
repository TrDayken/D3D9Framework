#ifndef __CELL_H__
#define __CELL_H__

#include <unordered_set>

#include "GameObject.h"

class GameObject;

class Cell
{
private:
	int x, y;

	std::unordered_set<GameObject* > objects;

	RECT cellrect;
public:

	Cell(int x, int y);
	~Cell();

	int getX();
	int getY();

	void AddObject(GameObject* obj);
	void RemoveObject(GameObject* obj);

	std::unordered_set<GameObject*> getCellObject();
};


#endif //!__CELL_H__