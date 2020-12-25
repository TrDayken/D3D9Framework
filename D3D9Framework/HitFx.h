#pragma once
#include "AbstractFXObject.h"
class HitFx :
	public AbstractFXObject
{
private:

	void LoadAnimation();

public:

	HitFx();

	void Render(Camera* camera);
};

