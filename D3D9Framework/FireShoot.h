#pragma once

#include <vector>

#include "GameObject.h"

#define BULLET_BBOX_WIDTH 24
#define BULLET_BBOX_HEIGHT 24
#define BULLET_VX 0.5
#define BULLET_GRAVITY 0.003f 
#define BULLET_BOUNCE 0.5f

class FireShoot :public GameObject
{
public:
	FireShoot(float x, float y, int direction);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void LoadAnimation();
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

