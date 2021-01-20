#include "GreenPiranha.h"

GreenPiranha::GreenPiranha()
{
	this->LoadAnimation();

	hideTime_start = GetTickCount();

	this->EntityTag = Tag::plant;

	state = PiranhaState::hide;

	this->ColTag == Collision2DTag::None;

	this->setRenderOrder(2);
}

GreenPiranha::~GreenPiranha()
{
}

void GreenPiranha::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["Idle"]->Render(RenderPosition.x, RenderPosition.y, this->Scale, direction);
}

void GreenPiranha::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + PIRANHA_WIDTH;
	b = this->Position.y + PIRANHA_HEIGHT;
}

void GreenPiranha::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Idle", animation->GetAnimation("ani-green-piranha-plant-attack"));
}

void GreenPiranha::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	this->Position.x += dx;
	this->Position.y += dy;

	switch (state)
	{
	case PiranhaState::hide:
	{
		distance = 0;
		if (GetTickCount() - hideTime_start > PIRANHA_HIDE)
		{
			state = PiranhaState::slideup;
		}
	}
	break;

	case PiranhaState::slideup:
	{
		vy = -PIRANHA_SPEED;
		distance += abs(vy * dt);
		if (distance > PIRANHA_HEIGHT)
		{
			vy = 0;
			distance = PIRANHA_HEIGHT;
			waitTime_start = GetTickCount();
			state = PiranhaState::idle;
		}
	}
	break;
	case PiranhaState::idle:
	{
		if (GetTickCount() - waitTime_start > PIRANHA_WAIT)
		{

			distance = 0;
			state = PiranhaState::slidedown;

		}
	}
	break;

	case PiranhaState::slidedown:
	{
		vy = PIRANHA_SPEED;
		distance += abs(vy * dt);
		if (distance > PIRANHA_HEIGHT)
		{
			vy = 0;
			distance = PIRANHA_HEIGHT;
			hideTime_start = GetTickCount();
			state = PiranhaState::hide;
		}
	}
	break;
	}
}
