#pragma once
#include "GameObject.h"

#define PIRANHA_WIDTH 48
#define PIRANHA_HEIGHT 72
#define PIRANHA_WAIT 3000
#define PIRANHA_HIDE 800

#define PIRANHA_GROWTIME 100

#define PIRANHA_SPEED 0.15f

enum class PiranhaState
{
	slideup,
	slidedown,
	idle,
	hide
};


class GreenPiranha :
	public GameObject
{
protected:

	DWORD waitTime_start, hideTime_start;

	float distance;

	PiranhaState state;

public:
	GreenPiranha();
	~GreenPiranha();

	virtual void Render(Camera* camera);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void LoadAnimation();

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);
};

