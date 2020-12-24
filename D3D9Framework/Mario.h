#ifndef __MARIO_H__
#define __MARIO_H__

#include <unordered_map>
#include <vector>

#include "MarioModel.h"
#include "GameObject.h"
#include "Camera.h"
#include "BigMario.h"
#include "SmallMario.h"
#include "FireMario.h"
#include "RacoonMario.h"

// mario physics settings
#define MARIO_GRAVITY 0.005f

#define MARIO_BBOX_X 48
#define MARIO_BBOX_Y 48

// mario level
#define DONTCHANGE	-1
#define SMALL		0
#define BIG			1
#define FIRE		2
#define RACOON		3
class Mario : public GameObject
{
private:
	//Mario's initial position
	float start_x;
	float start_y;

	Camera* camera;

	//Mario's state storage.
	std::vector<MarioModel*> StateofMario;
	MarioModel* CurrentMario;

	//Mario's gameplay mechanics 
	int Life, Coin; 

	int Combo;

	long Score; 

	//store mario cards, unimplemented.
	std::vector<int> Cards; 

public:
	Mario(float x = 0.0f, float y = 0.0f);
		
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects = NULL);
	virtual void Render(Camera* camera);
	virtual void OnOverLap(GameObject* obj);
	//virtual void LoadAnimation() {};

	void SetState(int state);
	void SetLevel(int level) { level = 1; }
	//void StartInvincibleFrame() { InvincibleFrame = 1; InvincibleTime = GetTickCount(); }

	MarioModel* GetCurrentMario(); 

	void Reset();
	void AnimationLoad();
	void SwitchMario(int level);
	void setCamera(Camera* camera);

	int getPmetter();

	//in game mechanics modification.
	void setCoin(int coin); 
	int getCoin(); 

	void setLife(int life); 
	int getLife(); 

	void setScore(long score); 
	long getScore(); 

	void ResetCombo(); 
	void ComboUp(); 
	int getCombo(); 

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif