#ifndef __MARIOMODEL_H__
#define __MARIOMODEL_H__

#include "GameObject.h"
//#include "Utils.h"
#include "Camera.h"
#include "AnimationManager.h"
//mario physic
#define MARIO_GRAVITY					0.005f
#define MARIO_ACCELERATION				0.002f
#define MARIO_DRAG						0.007f
#define MARIO_TOP_WALKING_SPEED			0.30f
#define MARIO_TOP_RUNNING_SPEED			0.5f
#define MARIO_MIN_SPEED					0.1f
#define MARIO_JUMP_FORCE				-0.95f
#define MARIO_MINIMUM_LIFT				-0.001f
// mario status
#define MARIO_HIGH_JUMP_TIME			200
#define MARIO_UNTOUCHABLE_TIME			5000
// mario collisionbox status
#define MARIO_BBOX_WIDTH				42
#define MARIO_BBOX_HEIGHT				80
#define MARIO_BBOX_HEIGHT_CROUCH		54
// small mario animation
#define ANI_SMALL_MARIO_IDLE		"ani-small-mario-idle"
#define ANI_SMALL_MARIO_WALK		"ani-small-mario-walk"
#define ANI_SMALL_MARIO_SKID		"ani-small-mario-skid"
#define ANI_SMALL_MARIO_RUN			"ani-small-mario-run"
#define ANI_SMALL_MARIO_JUMP		"ani-small-mario-jump"
#define ANI_SMALL_MARIO_CROUCH		"ani-small-mario-crouch"	
// big mario animation
#define ANI_BIG_MARIO_IDLE			"ani-big-mario-idle"
#define ANI_BIG_MARIO_WALK			"ani-big-mario-walk"
#define ANI_BIG_MARIO_SKID			"ani-big-mario-skid"
#define ANI_BIG_MARIO_RUN			"ani-big-mario-run"
#define ANI_BIG_MARIO_JUMP			"ani-big-mario-jump"
#define ANI_BIG_MARIO_CROUCH		"ani-big-mario-crouch"	
// racoon mario animation
#define ANI_RACOON_MARIO_IDLE		"ani-racoon-mario-idle"
#define ANI_RACOON_MARIO_WALK		"ani-racoon-mario-walk"
#define ANI_RACOON_MARIO_SKID		"ani-racoon-mario-skid"
#define ANI_RACOON_MARIO_RUN		"ani-racoon-mario-run"
#define ANI_RACOON_MARIO_JUMP		"ani-racoon-mario-jump"
#define ANI_RACOON_MARIO_CROUCH		"ani-racoon-mario-crouch"	
// fire mario animation
#define ANI_FIRE_MARIO_IDLE			"ani-fire-mario-idle"
#define ANI_FIRE_MARIO_WALK			"ani-fire-mario-walk"
#define ANI_FIRE_MARIO_SKID			"ani-fire-mario-skid"
#define ANI_FIRE_MARIO_RUN			"ani-fire-mario-run"
#define ANI_FIRE_MARIO_JUMP			"ani-fire-mario-jump"
#define ANI_FIRE_MARIO_CROUCH		"ani-fire-mario-crouch"	

enum class MovingStates
{
	Die,
	Idle,
	Walk,
	Run,
	Crouch,
	Attack
};

enum class JumpingStates
{
	Stand,
	Jump,
	Fall
};

struct MarioStateSet
{
	MovingStates movement;
	JumpingStates jump;
};

class MarioModel : public GameObject
{
protected:
	int InvincibleFrame;
	DWORD InvincibleTime_Start;

	DWORD HighJumpTime_Start;
	//Mario's initial position
	float start_x;
	float start_y;

	//mario acceleration 
	float acc_x;
	
	//mario states
	MarioStateSet state,prestate;

	//mario game's logic
	bool isOnGround;
	bool isHighJump;
public:
	MarioModel(float x = 0, float y = 0);

	//mario model update
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	// mario model render 
	virtual void Render(Camera* camera) = 0 ;

	void setMovestate(MovingStates move);
	void setJumpstate(JumpingStates jump);

	void OnKeyDown(int KeyCode);
	void OnKeyUp (int keyCode);
	void KeyState(BYTE* state);

	virtual void LoadAnimation() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) =0 ;
};

#endif