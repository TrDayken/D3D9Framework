#ifndef __ATTACKTAIL_H__
#define __ATTACKTAIL_H__

#include "GameObject.h"
#include "Camera.h"
#include "ScenceManager.h"

#define ATTACKTAIL_BBOX_WIDTH 100
#define ATTACKTAIL_BBOX_HEIGHT 30

#define RACOON_ATTACK_ANI_TIME	250

class AttackTail :public GameObject
{
	DWORD Deletetime;
public:
	AttackTail(float x, float y, int direction);

	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void OnOverLap(GameObject* obj);


	void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
};

#endif