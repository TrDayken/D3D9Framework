#pragma once
#include "AbstractFXObject.h"

#define DEBRIS_GRAVITY 0.0024f
#define COIN_BOUNCE 0.7f
#define DEBRIS_TIME 50 

class DebrisFx :
	public AbstractFXObject
{
	void LoadAnimation();

	DWORD Bounce_start;

public:

	DebrisFx();

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

};

