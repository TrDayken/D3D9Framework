#pragma once
#include "AbstractFXObject.h"

#define MARIO_GRAVITY 0.0024f
#define MARIO_BOUNCE 0.7f
#define MARIO_TIME 50 

class MarioDeathFx :public AbstractFXObject
{
	void LoadAnimation();

	DWORD Bounce_start;
public:
	MarioDeathFx();

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

