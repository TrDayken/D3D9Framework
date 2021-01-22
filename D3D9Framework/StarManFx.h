#pragma once
#include "AbstractFXObject.h"

#define FLY_SPEED 0.45

class StarManfx : public AbstractFXObject
{
	void LoadAnimation();
public:

	StarManfx();

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

