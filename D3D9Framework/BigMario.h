#ifndef __BIGMARIO_H__
#define __BIGMARIO_H__

#include <vector>
#include <d3dx9.h>

#include "MarioModel.h"
#include "Camera.h"

// big mario animation
#define ANI_BIG_MARIO_IDLE			"ani-big-mario-idle"
#define ANI_BIG_MARIO_WALK			"ani-big-mario-walk"
#define ANI_BIG_MARIO_SKID			"ani-big-mario-skid"
#define ANI_BIG_MARIO_RUN			"ani-big-mario-run"
#define ANI_BIG_MARIO_JUMP			"ani-big-mario-jump"
#define ANI_BIG_MARIO_CROUCH		"ani-big-mario-crouch"	
#define ANI_BIG_MARIO_HIGH_JUMP		"ani-big-mario-high-jump"
#define ANI_BIG_MARIO_HIGH_SPEED	"ani-big-mario-high-speed"

#define ANI_BIG_MARIO_HOLD_IDLE		"ani-big-mario-hold-idle"
#define ANI_BIG_MARIO_HOLD_JUMP		"ani-big-mario-hold-jump"
#define ANI_BIG_MARIO_HOLD			"ani-big-mario-hold"
#define ANI_BIG_MARIO_KICK			"ani-big-mario-kick"
// big mario bbox status
#define MARIO_BIG_BBOX_WIDTH				42
#define MARIO_BIG_BBOX_HEIGHT				80
#define MARIO_BIG_BBOX_HEIGHT_CROUCH		54

#define ANI_BIG_MARIO_WARP					"ani-big-mario-idle-front"

class BigMario : public MarioModel
{
private:
	void BigMarioRunandWalkState();
public:
	BigMario();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int getCurrentLevel();
};

#endif