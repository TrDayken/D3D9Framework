#ifndef __KOOPA_H__
#define __KOOPA_H__

#include "Camera.h"
#include "GameObject.h"
#include "ScenceManager.h"
#include "Global_Variable.h"
#include "Camera.h"
//koopa physics
#define KOOPA_WALKING_SPEED			0.005f
#define KOOPA_SLIDE_SPEED			0.03f
#define KOOPA_GRAVITY				0.003f
#define KOOPA_TIME_DIE				300
//koopa bbox settings
#define KOOPA_BBOX_WIDTH			48
#define KOOPA_BBOX_HEIGHT			78
#define KOOPA_BBOX_HEIGHT_SHELL		48
//koopa animation setting
#define ANI_RED_KOOPA_MOVE		"ani-red-koopa-troopa-move"
#define ANI_RED_KOOPA_CROUCH	"ani-red-koopa-troopa-crouch"
#define ANI_RED_KOOPA_IDLE		"ani-red-koopa-troopa-shell-idle"
#define ANI_RED_KOOPA_SLIDE		"ani-red-koopa-troopa-shell-run"

enum class KoopaState
{
	die,
	walking,
	shell,
	slide,
};


class Koopa :public GameObject
{
	KoopaState koopstate;
	DWORD DelayDeadTime_start;
public:
	Koopa();

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);

	void setIsBeingHold(bool isBeingHold);

	void SetState(KoopaState state);
	void OnOverLap(GameObject* obj);
	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);
};

#endif // !__KOOPA_H__