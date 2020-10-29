#ifndef __MARIO_H__
#define __MARIO_H__

#include "GameObject.h"
#include "Camera.h"

#define MARIO_GRAVITY 0.005f


class Mario : public GameObject
{
private:
	int InvincibleFrame;
	DWORD InvincibleTime;

	//Mario's initial position
	float start_x;
	float start_y;

	Camera* camera;
public:
	Mario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects = NULL);
	virtual void Render();
	virtual void Render(Camera* camera);

	void SetState(int state);
	void SetLevel(int level) { level = 1; }
	void StartInvincibleFrame() { InvincibleFrame = 1; InvincibleTime = GetTickCount(); }

	void Reset();
	void AnimationLoad();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

#endif