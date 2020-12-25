#pragma once
#include "GameObject.h"


#define VENUS_WIDTH 48
#define VENUS_HEIGHT 92
#define VENUS_WAIT 1000
#define VENUS_HIDE 800

#define VENUS_GROWTIME 100

#define VENUS_SPEED 0.15f

enum class VenusState
{
	slideup,
	slidedown,
	idle,
	hide
};

enum class VenusHead
{
	up = -1,
	down = 1
};

class RedVenus :
	public GameObject
{
protected:

	DWORD waitTime_start, hideTime_start; 

	float distance; 

	VenusState state;

	VenusHead head; 

	void ShootFireBall(); 
public: 
	RedVenus();
	~RedVenus();

	virtual void Render(Camera* camera);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void LoadAnimation();

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
};

