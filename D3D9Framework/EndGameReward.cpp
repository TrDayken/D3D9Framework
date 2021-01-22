#include "EndGameReward.h"
#include "SpriteManager.h"
#include "Game.h"
#include "Global_Variable.h"
#include "ScenceManager.h"
#include "FXObjectManager.h"

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

	if (collected)
	{
		ScenceManager::GetInstance()->getCurrentScence()->getCamera()->setIsStatic(true);
		ScenceManager::GetInstance()->getCurrentScence()->getCamera()->setScrollX(true);
		//ScenceManager::GetInstance()->getCurrentScence()->getCamera()->setCameraPosition(Vector2(this->Position.x -360, this->Position.y -264));
	}
}

void EndGameReward::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(Position.x, Position.y);

	if (!collected)
		items[reward]->Draw(pos.x, pos.y);

	if (collected)
	{
		Game::GetInstance()->GetFont()->RenderText("COURSE CLEAR", Vector2(pos.x -150,pos.y -200));

		Game::GetInstance()->GetFont()->RenderText("YOU GOT A CARD", Vector2(pos.x - 200, pos.y - 125));

		switch (finalreward)
		{

		case 0:
			cards[finalreward]->Draw(pos.x + 175, pos.y -125);
			break;
		case 1:
			cards[finalreward]->Draw(pos.x + 175, pos.y -125);
			break;
		case 2:
			cards[finalreward]->Draw(pos.x + 175, pos.y -125);
			break;

		default:
			break;
		}
	}
}

void EndGameReward::LoadAnimation()
{
	auto sprite = SpriteManager::GetInstance();

	items[0] = sprite->GetSprite("spr-super-mushroom-0");
	items[1] = sprite->GetSprite("spr-fire-flower-0");
	items[2] = sprite->GetSprite("spr-star-man-0");

	cards[0] = sprite->GetSprite("spr-super-mushroom-card-0");
	cards[1] = sprite->GetSprite("spr-fire-flower-card-0");
	cards[2] = sprite->GetSprite("spr-star-man-card-0");
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
			finalreward = reward ;
			Global_Variable::GetInstance()->setCard(this->reward + 1 );
			this->collected = true;

			switch (finalreward)
			{
			case 0:
				FXObjectManager::GetInstance()->CreateFx("mushroom", this->Position);
				break;
			case 1:
				FXObjectManager::GetInstance()->CreateFx("fireflower", this->Position);
				break;
			case 2:
				FXObjectManager::GetInstance()->CreateFx("starman", this->Position);
				break;
			default:
				break;
			}
		}
	}
}
