#ifndef __MARIOMODEL_H__
#define __MARIOMODEL_H__

#include "GameObject.h"
//#include "Utils.h"
#include "Camera.h"
#include "AnimationManager.h"
#include "ScenceManager.h"
#include "Goomba.h"
#include "Koopa.h"

//mario physic
#define MARIO_GRAVITY					0.005f
#define MARIO_ACCELERATION				0.002f
#define MARIO_DRAG						0.007f
#define MARIO_TOP_WALKING_SPEED			0.30f
#define MARIO_TOP_RUNNING_SPEED			0.4f
#define MARIO_MIN_SPEED					0.1f
#define MARIO_JUMP_FORCE				-0.95f
#define MARIO_MINIMUM_LIFT				-0.001f
#define MARIO_DEFLECT_MOB				0.95f

// mario status
#define MARIO_HIGH_JUMP_TIME			200
#define MARIO_UNTOUCHABLE_TIME			5000
#define MARIO_PMETTER					7
#define MARIO_PLUS_PMETTER_TIME			300
#define MARIO_DECAY_PEMETTER_TIME		250

// mario collisionbox status
#define MARIO_BBOX_WIDTH				42
#define MARIO_BBOX_HEIGHT				80
#define MARIO_BBOX_HEIGHT_CROUCH		54


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
	Fall,
	Float,
	Fly
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
	DWORD IncreasePMetterTime_Start;
	DWORD DecayPMetterTime_Start;
	//Mario's initial position
	float start_x;
	float start_y;

	//mario acceleration 
	float acc_x;
	
	//mario states
	MarioStateSet state,prestate;
	int changestate;
	//mario game's logic
	bool canFly = false;
	bool fullMetter = false;
	bool isOnGround;
	bool isHighJump;
	bool isIncreasingPMetter = false;
	int  PMetter = 0;
	GameObject* Hold;
public:
	MarioModel(float x = 0, float y = 0);

	//mario model update
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	// mario model render 
	virtual void Render(Camera* camera) = 0 ;

	void setMovestate(MovingStates move);
	void setJumpstate(JumpingStates jump);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp (int keyCode);
	virtual void KeyState(BYTE* state);

	virtual void LoadAnimation() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) =0 ;
	int getLevel();
	void SetLevel(int level);
	void SetPosition(int x, int y);
};

#endif