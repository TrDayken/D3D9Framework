#ifndef __RACCOONPOWERUPS_H__
#define __RACCOONPOWERUPS_H__

#include "GameObject.h"

#define LEAF_REVEAL_TIME 300
#define LEAF_REVEAL_VY 0.4f

#define LEAF_GRAVITY  0.0012f
#define LEAF_FALLING_VEL 0.055f
#define LEAF_FALLING_VX 0.15f
#define LEAF_CYCLE_TIME 900

#define LEAF_WIDTH 48
#define LEAF_HEIGHT 42

class RaccoonPowerUps : public GameObject
{
	void LoadAnimation();

	int state;

	DWORD leaf_reveal_time, cycle_time;
public:
	RaccoonPowerUps();

	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void OnOverLap(GameObject* obj);

};

#endif