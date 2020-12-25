#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH 24
#define BULLET_BBOX_HEIGHT 24

#define BULLET_VX 0.3f
#define BULLET_VY 0.3f
#define ANI_BULLET	"ani-fire-ball"

class VenusFireShoot :
	public GameObject
{
private: 



public: 
	VenusFireShoot(float x, float y, int direction, int vertical);

	~VenusFireShoot();

	virtual void Render(Camera* camera);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void LoadAnimation();

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void OnOverLap(GameObject* object);
};

