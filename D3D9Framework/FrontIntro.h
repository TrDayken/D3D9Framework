#pragma once
#include "AnimationManager.h"
#include "Camera.h"

class FrontIntro
{
public:

	void load();
	
	void update(DWORD dt);

	void render(Camera* camera);
};

