#pragma once

#include "RedMushroomPowerUps.h"
class GreenShroom: public RedMushroomPowerUps
{
public:
	GreenShroom();

	void LoadAnimation();

	virtual void OnOverLap(GameObject* obj) override;
};

