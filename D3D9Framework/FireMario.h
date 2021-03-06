#ifndef __FIREMARIO_H__
#define __FIREMARIO_H__

#include <vector>
#include <d3dx9.h>

#include "MarioModel.h"
#include "Camera.h"
#include "FireShoot.h"
#include "ScenceManager.h"

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
#define ANI_FIRE_MARIO_ATTACK			"ani-fire-mario-throw"

#define ANI_FIRE_MARIO_HOLD_IDLE		"ani-fire-mario-hold-idle"
#define ANI_FIRE_MARIO_HOLD_JUMP		"ani-fire-mario-hold-jump"
#define ANI_FIRE_MARIO_HOLD			"ani-fire-mario-hold"

#define ANI_FIRE_MARIO_WARP				"ani-fire-mario-idle-front"

// fire mario bbox status
#define MARIO_FIRE_BBOX_WIDTH				42
#define MARIO_FIRE_BBOX_HEIGHT				80
#define MARIO_FIRE_BBOX_HEIGHT_CROUCH		54

// fire mario status
#define FIREMARIO_COOLDOWN_ATTACK 3500
#define FIREMARIO_ANI_ATTACKTIME 200
class FireMario : public MarioModel
{
private:
	void FireMarioRunandWalkState();
	DWORD timeAttackani_Start;
	DWORD timeAttack_Start;

	bool attackani;
	bool canattack;

public:
	FireMario();


	void OnKeyDown(int KeyCode);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int getCurrentLevel();
};

#endif