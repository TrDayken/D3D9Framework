#pragma once
#include "GameObject.h"
class DeathBox :
	public GameObject
{
public:
	DeathBox();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnOverLap(GameObject* obj);
};

