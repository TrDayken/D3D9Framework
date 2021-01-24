#pragma once
#include "GameObject.h"
class Curtain :
	public GameObject
{
public: 
	Curtain();

	void LoadAnimation();

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

