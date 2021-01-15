#ifndef __GOOMBA_H__
#define __GOOMBA_H__

#include "Camera.h"
#include "GameObject.h"
#include "ScenceManager.h"
#include "Global_Variable.h"
#include "Camera.h"

// goomba physics
#define GOOMBA_WALKING_SPEED			0.005f
#define GOOMBA_GRAVITY					0.004f
#define GOOMBA_FLYDIE_FORCE_VY			0.095f
// goomba time config
#define GOOMBA_TIME_DIE					1000
#define GOOMBA_TIME_FLYDIE				50
// goomba bbox settings
#define GOOMBA_BBOX_WIDTH				48
#define GOOMBA_BBOX_HEIGHT				48
#define GOOMBA_BBOX_HEIGHT_DIE			27
// goomba animations setting
#define ANI_GOOMBA_WALK		"ani-goomba-walk"
#define ANI_GOOMBA_DIE		"ani-goomba-die"
#define ANI_GOOMBA_IDLE		"ani-goomba-idle"
#define ANI_GOOMBA_FLY		"ani-red-para-goomba-fly"

#define RED_PARAGOOMBA_HIGH_JUMP  1.0f
#define RED_PARAGOOMBA_LOW_JUMP  0.5f
#define DELAY_PATTERN			1500
enum class GoombaState
{
	die,
	walking,
	flying,
	flydie
};

class Goomba : public GameObject
{
protected:
	GoombaState goomstate;
	DWORD DelayDeadTime_start;
	DWORD FlyDieTime_start;

	int jumpcount = 0;
	DWORD DelayPattern_start;

public:

	Goomba();

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render(Camera* camera);
	
	void SetState(GoombaState state);

	void OnOverLap(GameObject* obj);

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);
};

#endif