#include "RaccoonPowerUps.h"
#include "AnimationManager.h"

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
}

void RaccoonPowerUps::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["Idle"]->Render(RenderPosition.x, RenderPosition.y, -direction);
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

	switch (state)
	{
	case 1:
	{
		if (GetTickCount() - leaf_reveal_time > LEAF_REVEAL_TIME)
		{
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
		vx = LEAF_FALLING_VX * direction; 
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
}
