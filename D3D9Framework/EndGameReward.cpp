#include "EndGameReward.h"
#include "SpriteManager.h"

EndGameReward::EndGameReward()
{
	LoadAnimation(); 

	timer = GetTickCount();
}

EndGameReward::~EndGameReward()
{
}

void EndGameReward::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount() - timer >= REWARD_CYCLE_TIME)
	{
		timer = GetTickCount();

		reward++;

		if (reward > 2)
			reward = 0; 
	}
}

void EndGameReward::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(Position.x, Position.y);

	items[reward]->Draw(pos.x, pos.y);
}

void EndGameReward::LoadAnimation()
{
	auto sprite = SpriteManager::GetInstance();

	items[0] = sprite->GetSprite("spr-super-mushroom-0");
	items[1] = sprite->GetSprite("spr-fire-flower-0");
	items[2] = sprite->GetSprite("spr-star-man-0");
}

void EndGameReward::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void EndGameReward::OnOverLap(GameObject* obj)
{
}
