#include "EndGameReward.h"
#include "SpriteManager.h"
#include "Game.h"
#include "Global_Variable.h"

EndGameReward::EndGameReward()
{
	LoadAnimation(); 

	timer = GetTickCount();

	this->collected = false;

	this->ColTag = Collision2DTag::None; 

	this->setRenderOrder(1);
}

EndGameReward::~EndGameReward()
{
}

void EndGameReward::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

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

	if (!collected)
		items[reward]->Draw(pos.x, pos.y);

	if (collected)
		Game::GetInstance()->GetFont()->RenderText("COURSE CLEAR", pos);
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
	left = this->Position.x;

	top = this->Position.y;

	right = this->Position.x + REWARD_BBOX_X;

	bottom = this->Position.y + REWARD_BBOX_Y;
}

void EndGameReward::OnOverLap(GameObject* obj)
{
	if (!collected)
	{
		if (obj->EntityTag == Tag::player)
		{
			Global_Variable::GetInstance()->setCard(this->reward + 1 );
			this->collected = true;
		}
	}
}
