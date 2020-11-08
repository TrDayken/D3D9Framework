#ifndef __GOOMBA_H__
#define __GOOMBA_H__

#include "Camera.h"
#include "GameObject.h"
#include "ScenceManager.h"
#include "Global_Variable.h"
#include "Camera.h"

#define GOOMBA_WALKING_SPEED 0.05f;
#define GOOMBA_GRAVITY  0.003f
#define GOOMBA_FLY_DIE 0.9f

#define GOOMA_TIME_DIE 300

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 48
#define GOOMBA_BBOX_HEIGHT_DIE 27

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ANI_GOOMBA_WALK	"ani-goomba-walk"
#define ANI_GOOMBA_DIE		"ani-goomba-die"
#define ANI_GOOMBA_IDLE		"ani-goomba-idle"

class Goomba : public GameObject
{
	bool flydie;
	DWORD timedie;
public:

	Goomba();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render(Camera* camera);
	virtual void LoadAnimation();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
};

#endif