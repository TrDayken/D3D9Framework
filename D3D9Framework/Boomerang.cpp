#include "Boomerang.h"
#include "AnimationManager.h"
#include "ScenceManager.h"
Boomerang::Boomerang(float x, float y, int direction, int vertical)
{
	ColTag = Collision2DTag::None;

	EntityTag = Tag::enemyprojectile;

	this->Position.x = x;
	this->Position.y = y;
	LoadAnimation();

	this->waittime = GetTickCount();

	this->setRenderOrder(5);

	this->start_y = y;

	this->state = 0;

}

void Boomerang::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Default", animation->GetAnimation("ani-boomerang-spin"));
}

void Boomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->Position.x;
	top = this->Position.y;
	right = this->Position.x + WIDTH;
	bottom = this->Position.y + HEIGHT;
}

void Boomerang::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;

	switch (state)
	{
	case 0:
		vx = VX;
		vy = -VY;
		if (GetTickCount() - waittime > PITCHTIME)
		{
			state = 1;
			waittime = GetTickCount();
		}
		break;
	case 1:
		vx = VX;
		vy = VY;
		if (this->Position.y > start_y)
		{
			state = 2;
		}
		break;
	case 2:
		vx = -VX;
		vy = 0;
		break;

	default:
		break;
	}
}

void Boomerang::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["Default"]->Render(RenderPosition.x, RenderPosition.y, this->Scale, direction);

}

void Boomerang::OnOverLap(GameObject* object)
{
	if (object->EntityTag == Tag::enemy)
	{
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
	}
}
