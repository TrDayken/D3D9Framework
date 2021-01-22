#pragma once
#include "ScenceManager.h"
#include "Global_Variable.h"
#include "Camera.h"
#include "Koopa.h"

//koopa physics
#define KOOPA_WALKING_SPEED			0.005f
#define KOOPA_SLIDE_SPEED			0.044f
#define KOOPA_GRAVITY				0.003f
#define KOOPA_TIME_DIE				300

#define KOOPA_CYCLE_TIME			1500
//koopa bbox settings
#define KOOPA_BBOX_WIDTH			48
#define KOOPA_BBOX_HEIGHT			78
#define KOOPA_BBOX_HEIGHT_SHELL		45
//koopa animation setting
#define ANI_RED_KOOPA_MOVE		"ani-green-koopa-troopa-move"
#define ANI_RED_KOOPA_CROUCH	"ani-green-koopa-troopa-crouch"
#define ANI_RED_KOOPA_IDLE		"ani-green-koopa-troopa-shell-idle"
#define ANI_RED_KOOPA_SLIDE		"ani-green-koopa-troopa-shell-run"

//enum class KoopaState
//{
//	die,
//	walking,
//	shell,
//	slide,
//	fly
//};


class GreenKoopa :
	public GameObject
{
	KoopaState koopstate;
	DWORD DelayDeadTime_start;

	DWORD Cycletime;
	float maxleft, maxright;
public:
	GreenKoopa();

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);

	void setIsBeingHold(bool isBeingHold);

	void SetState(KoopaState state);
	void OnOverLap(GameObject* obj);
	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);

	void UpdatePosition();

	void setVx(float vx) override;

	virtual void flying();
};

