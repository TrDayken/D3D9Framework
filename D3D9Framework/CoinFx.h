#pragma once
#include "AbstractFXObject.h"

#define COIN_GRAVITY 0.0024f
#define COIN_BOUNCE 0.7f
#define COIN_TIME 50 

class CoinFx :
	public AbstractFXObject
{
	void LoadAnimation();

	DWORD Bounce_start; 
public:

	CoinFx();

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

