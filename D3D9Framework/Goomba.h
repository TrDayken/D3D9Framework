#ifndef __GOOMBA_H__
#define __GOOMBA_H__

#include "Camera.h"
#include "GameObject.h"
#include "ScenceManager.h"
#include "Global_Variable.h"
#include "Camera.h"

#define GOOMBA_WALKING_SPEED 0.005f
#define GOOMBA_GRAVITY  0.003f

#define GOOMA_TIME_DIE 300

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 48
#define GOOMBA_BBOX_HEIGHT_DIE 27

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ANI_GOOMBA_WALK		"ani-goomba-walk"
#define ANI_GOOMBA_DIE		"ani-goomba-die"
#define ANI_GOOMBA_IDLE		"ani-goomba-idle"

class Goomba : public GameObject
{
	DWORD DelayDeadTime_start;
public:

	Goomba();
	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	
	void SetState(int state);
	
	void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
};

#endif