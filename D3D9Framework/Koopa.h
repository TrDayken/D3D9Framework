#ifndef __KOOPA_H__
#define __KOOPA_H__

#include "Camera.h"
#include "GameObject.h"
#include "ScenceManager.h"
#include "Global_Variable.h"
#include "Camera.h"

#define KOOPA_WALKING_SPEED			0.005f
#define KOOPA_SLIDE_SPEED			0.05f
#define KOOPA_GRAVITY				0.003f
#define KOOPA_TIME_DIE				300

#define KOOPA_BBOX_WIDTH			48
#define KOOPA_BBOX_HEIGHT			78
#define KOOPA_BBOX_HEIGHT_SHELL		48

enum class KoopaState
{
	die,
	walking,
	shell,
	slide,
};

#define ANI_RED_KOOPA_MOVE		"ani-red-koopa-troopa-move"
#define ANI_RED_KOOPA_CROUCH	"ani-red-koopa-troopa-crouch"

#define ANI_RED_KOOPA_IDLE		"ani-red-koopa-troopa-shell-idle"
#define ANI_RED_KOOPA_SLIDE		"ani-red-koopa-troopa-shell-run"
class Koopa :public GameObject
{
	KoopaState koopstate;
	DWORD DelayDeadTime_start;
public:
	Koopa();

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);

	void SetState(KoopaState state);

	void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
};

#endif // !__KOOPA_H__