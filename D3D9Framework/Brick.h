#ifndef __BRICK_H__
#define __BRICK_H__

#include "GameObject.h"

#define BRICK_BBOX_WIDTH 48
#define BRICK_BBOX_HEIGHT 48

#define BRICK_STATE 0
#define COIN_STATE 1

class Brick : public GameObject
{
public:
	Brick();

	void LoadAnimation();

	void Render(Camera* camera);

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);

	void OnOverLap(GameObject* obj);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Explode();
};

#endif
