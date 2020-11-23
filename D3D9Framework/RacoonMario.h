#ifndef __RACOONMARIO_H__
#define __RACOONMARIO_H__

#include <vector>
#include <d3dx9.h>

#include "MarioModel.h"
#include "Camera.h"
#include "Animation.h"
#include "AttackTail.h"

// raccoon mario animation
#define ANI_RACCOON_MARIO_IDLE				"ani-raccoon-mario-idle"
#define ANI_RACCOON_MARIO_WALK				"ani-raccoon-mario-walk"
#define ANI_RACCOON_MARIO_SKID				"ani-raccoon-mario-skid"
#define ANI_RACCOON_MARIO_RUN				"ani-raccoon-mario-speed-up"
#define ANI_RACCOON_MARIO_JUMP				"ani-raccoon-mario-jump"
#define ANI_RACCOON_MARIO_CROUCH			"ani-raccoon-mario-crouch"	

#define ANI_RACCOON_MARIO_FLOAT				"ani-raccoon-mario-float"
#define ANI_RACCOON_MARIO_FLY				"ani-raccoon-mario-fly"
#define ANI_RACCOON_MARIO_SPIN				"ani-raccoon-mario-spin"
#define ANI_RACCOON_MARIO_HOLD_IDLE			"ani-raccoon-mario-hold-idle"
#define ANI_RACCOON_MARIO_HOLD_MOVE			"ani-raccoon-mario-hold"
#define ANI_RACCOON_MARIO_KICK				"ani-raccoon-mario-kick"
// raccoon mario bbox status
#define MARIO_RACCOON_BBOX_WIDTH					42
#define MARIO_RACCOON_BBOX_HEIGHT					80
#define MARIO_RACCOON_BBOX_HEIGHT_CROUCH			54

// raccoon status
#define RACCOON_MARIO_FLYTIME	3000
#define RACCOON_MARIO_FLOATTIME 5000

#define FLOAT_GRAVITY			0.05f
#define RACCOON_MARIO_FLY_FROCE		0.03f
#define RACCOON_MARIO_FLOAT_FROCE	0.002f

#define RACOON_ATTACK_ANI_TIME	250
#define RACOON_ATTACK_COOLDOWN	300
class RacoonMario : public MarioModel
{
private:
	void RacoonMarioRunandWalkState();

	DWORD Pushtime;
	DWORD Flyingtime_start;
	//int flying = 0;
	bool holdFloat;
	bool isFlying;
	bool isFloating;


	//mario attack and attack animation
	DWORD timeAttackani_Start;
	DWORD timeAttack_Start;

	bool readytoAttack = true;
	bool attackani;
	bool canattack;
public:
	RacoonMario();


	void OnKeyDown(int KeyCode);
	void KeyState(BYTE* state);
	void OnKeyUp(int KeyCode);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int getCurrentLevel();
};

#endif