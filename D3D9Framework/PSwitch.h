#pragma once
#include "GameObject.h"

#define PSWITCH_BBOX_WIDTH 48
#define PSWITCH_BBOX_HEIGHT 48

#define PSWITCH_PRESSED_BBOX_HEIGHT 21

class PSwitch :
	public GameObject
{
private:
	bool ispressed;

public:
	PSwitch();

	void LoadAnimation();

	void Render(Camera* camera);

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);

	void OnOverLap(GameObject* obj);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

};

