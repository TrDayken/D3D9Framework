#ifndef __REDMUSHROOMPOWERUPS_H__
#define __REDMUSHROOMPOWERUPS_H__

#include "GameObject.h"

#define MUSHROOM_SPEED  0.15f
#define MUSHROOM_GRAVITY  0.0024f

#define SPROUT_SPEED  0.1f

#define MUSHROOM_WIDTH 48
#define MUSHROOM_HEIGHT 48

class RedMushroomPowerUps : public GameObject
{
	void LoadAnimation();

	int state;
public:
	RedMushroomPowerUps();

	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void OnOverLap(GameObject* obj);
};

#endif