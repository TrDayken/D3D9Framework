#include "BrickFx.h"
#include "FXObjectManager.h"

BrickFx::BrickFx()
{
	const float velx[4] = { +0.15f, +0.20f, -0.20f, -0.15f };
	const float vely[4] = { -0.30f, -0.60f, -0.60f, -0.30f };

	for (int i = 0; i < 4; i++)
	{
		auto fx = FXObjectManager::GetInstance()->CreateFx("debris",this->Position);
		fx->setForce(Vector2(velx[i], vely[i]));
	}
}
