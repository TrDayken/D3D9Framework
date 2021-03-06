#ifndef __SMALLMARIO_H__
#define __SMALLMARIO_H__

#include <vector>
#include <d3dx9.h>

#include "MarioModel.h"
#include "Camera.h"

// small mario animation
#define ANI_SMALL_MARIO_IDLE		"ani-small-mario-idle"
#define ANI_SMALL_MARIO_WALK		"ani-small-mario-walk"
#define ANI_SMALL_MARIO_SKID		"ani-small-mario-skid"
#define ANI_SMALL_MARIO_RUN			"ani-small-mario-run"
#define ANI_SMALL_MARIO_JUMP		"ani-small-mario-jump"
#define ANI_SMALL_MARIO_CROUCH		"ani-small-mario-crouch"	

#define ANI_SMALL_MARIO_HOLD_IDLE		"ani-small-mario-hold-idle"
#define ANI_SMALL_MARIO_HOLD_JUMP		"ani-small-mario-hold-jump"
#define ANI_SMALL_MARIO_HOLD			"ani-small-mario-hold"

#define ANI_SMALL_MARIO_WARP				"ani-small-mario-idle-front"

// small mario bbox status
#define MARIO_SMALL_BBOX_HEIGHT	45
#define MARIO_SMALL_BBOX_WIDTH	39
class SmallMario : public MarioModel
{
private:
	void SmallMarioRunandWalkState();
public:
	SmallMario();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int getCurrentLevel();
};

#endif