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
#define SMALL	1
#define BIG		2
#define FIRE	3
#define RACOON	4
class Mario : public GameObject
{
private:
	//Mario's initial position
	float start_x;
	float start_y;

	Camera* camera;

	std::vector<MarioModel*> StateofMario;
	MarioModel* CurrentMario;
public:
	Mario(float x = 0.0f, float y = 0.0f);
		
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects = NULL);
	//virtual void Render();
	virtual void Render(Camera* camera);

	void SetState(int state);
	void SetLevel(int level) { level = 1; }
	//void StartInvincibleFrame() { InvincibleFrame = 1; InvincibleTime = GetTickCount(); }

	MarioModel* GetCurrentMario();

	void Reset();
	void AnimationLoad();

	void setCamera(Camera* camera);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif