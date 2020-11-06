#ifndef __FIREMARIO_H__
#define __FIREMARIO_H__

#include <vector>
#include <d3dx9.h>

#include "MarioModel.h"
#include "Camera.h"

// fire mario animation
#define ANI_FIRE_MARIO_IDLE				"ani-fire-mario-idle"
#define ANI_FIRE_MARIO_WALK				"ani-fire-mario-walk"
#define ANI_FIRE_MARIO_SKID				"ani-fire-mario-skid"
#define ANI_FIRE_MARIO_RUN				"ani-fire-mario-run"
#define ANI_FIRE_MARIO_JUMP				"ani-fire-mario-jump"
#define ANI_FIRE_MARIO_CROUCH			"ani-fire-mario-crouch"	
#define ANI_FIRE_MARIO_HIGH_JUMP		"ani-fire-mario-high-jump"
#define ANI_FIRE_MARIO_HIGH_SPEED		"ani-fire-mario-high-speed"
#define ANI_FIRE_MARIO_HOLD				"ani-fire-mario-hold"
#define ANI_FIRE_MARIO_KICK				"ani-fire-mario-kick"

// fire mario bbox status
#define MARIO_FIRE_BBOX_WIDTH				42
#define MARIO_FIRE_BBOX_HEIGHT				80
#define MARIO_FIRE_BBOX_HEIGHT_CROUCH		54

class FireMario : public MarioModel
{
private:
	void FireMarioRunandWalkState();
public:
	FireMario();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif