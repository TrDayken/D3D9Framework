#pragma once
#include "GameObject.h"

#define WIDTH 16
#define HEIGHT 24

#define MOVE_SPEED 0.05

#define CYCLE 1500
#define WAIT 3000

#define BOOMER_TIME_FLYDIE				50

#define BOOMER_GRAVITY					0.004f
#define BOOMER_FLYDIE_FORCE_VY			0.095f
class BoomerangBrother :
	public GameObject
{

	int state;

	DWORD waittime;

	bool die = false;

	DWORD FlyDieTime_start;

public:

	BoomerangBrother();

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render(Camera* camera);

	void Throw();

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);

	void OnOverLap(GameObject* obj) override;
};


