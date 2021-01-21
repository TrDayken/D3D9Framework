#include "RaccoonPowerUps.h"
#include "AnimationManager.h"
#include "ScenceManager.h"

void RaccoonPowerUps::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Idle", animation->GetAnimation("ani-super-leaf-red"));
}

RaccoonPowerUps::RaccoonPowerUps()
{
	LoadAnimation();

	state = 1;

	this->EntityTag = Tag::leaf;

	leaf_reveal_time = GetTickCount();

	collected = false; 

	this->ColTag = Collision2DTag::None; 

	this->setRenderOrder(0);
}

void RaccoonPowerUps::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["Idle"]->Render(RenderPosition.x, RenderPosition.y, this->Scale, direction);
}

void RaccoonPowerUps::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = Position.x;
	t = Position.y;
	r = Position.x + LEAF_WIDTH;
	b = Position.y + LEAF_HEIGHT;
}

void RaccoonPowerUps::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObject)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	if (collected)
		if (GetTickCount() - timecollected >= DELAY)
		{
			ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
		}

	switch (state)
	{
	case 1:
	{
		if (GetTickCount() - leaf_reveal_time > LEAF_REVEAL_TIME)
		{
			this->setRenderOrder(5);
			cycle_time = GetTickCount();
			vy = 0;
			state = 2;
		}
		else
		{
			vy = -LEAF_REVEAL_VY;
		}
	}
	break;
	case 2:
	{
		vy = LEAF_FALLING_VEL;
		vx = -LEAF_FALLING_VX * direction; 
	}
	break;
	}

	if (GetTickCount() - cycle_time > LEAF_CYCLE_TIME)
	{
		direction = -direction;
		cycle_time = GetTickCount();
	}
}

void RaccoonPowerUps::OnOverLap(GameObject* obj)
{
	if (obj->EntityTag == Tag::player)
	{
		if (!collected)
		{
			timecollected = GetTickCount();

			collected = true;
		}
	}
}
