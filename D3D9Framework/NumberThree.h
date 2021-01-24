#pragma once
#include "GameObject.h"
class NumberThree :
	public GameObject
{
public:
	NumberThree();

	void LoadAnimation();

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

