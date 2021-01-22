#pragma once
#include "AbstractFXObject.h"

#define FLY_SPEED 0.45

class FireFlowerFx	: public AbstractFXObject
{
	void LoadAnimation();
public:

	FireFlowerFx();

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

