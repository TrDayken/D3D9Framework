#ifndef __RACOONMARIO_H__
#define __RACOONMARIO_H__

#include <vector>
#include <d3dx9.h>

#include "MarioModel.h"
#include "Camera.h"

// big mario animation
#define ANI_RACCOON_MARIO_IDLE				"ani-raccoon-mario-idle"
#define ANI_RACCOON_MARIO_WALK				"ani-raccoon-mario-walk"
#define ANI_RACCOON_MARIO_SKID				"ani-raccoon-mario-skid"
#define ANI_RACCOON_MARIO_RUN				"ani-raccoon-mario-run"
#define ANI_RACCOON_MARIO_JUMP				"ani-raccoon-mario-jump"
#define ANI_RACCOON_MARIO_CROUCH			"ani-raccoon-mario-crouch"	

#define ANI_RACCOON_MARIO_HIGH_JUMP			"ani-raccoon-mario-high-jump"
#define ANI_RACCOON_MARIO_HIGH_SPEED		"ani-raccoon-mario-high-speed"
#define ANI_RACCOON_MARIO_HOLD				"ani-raccoon-mario-hold"
#define ANI_RACCOON_MARIO_KICK				"ani-raccoon-mario-kick"
// big mario bbox status
#define MARIO_RACCOON_BBOX_WIDTH					42
#define MARIO_RACCOON_BBOX_HEIGHT					80
#define MARIO_RACCOON_BBOX_HEIGHT_CROUCH			54

class RacoonMario : public MarioModel
{
private:
	void RacoonMarioRunandWalkState();
public:
	RacoonMario();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif