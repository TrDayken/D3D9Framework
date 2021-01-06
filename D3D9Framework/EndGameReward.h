#pragma once
#include "GameObject.h"

#define REWARD_CYCLE_TIME 70 
#define REWARD_BBOX_X 48
#define REWARD_BBOX_Y 48

class EndGameReward :
	public GameObject
{
private:

	Sprite* items[3];

	int timer;
	int reward;

public:

	EndGameReward();

	~EndGameReward();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render(Camera* camera);

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void OnOverLap(GameObject* obj);
};

