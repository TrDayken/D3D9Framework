#pragma once
#include "GameObject.h"

#define WIDTH 32
#define HEIGHT 32

#define VX 0.25
#define VY 0.1

#define PITCHTIME 700

class Boomerang :
	public GameObject
{

	int state;

	DWORD waittime;

	float start_y;
public :
	Boomerang(float x, float y, int direction, int vertical);

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render(Camera* camera);

	void OnOverLap(GameObject* object);
};

