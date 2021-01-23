#include "BoomerangBrother.h"
#include "AnimationManager.h"
#include "ScenceManager.h"
#include "Boomerang.h"

BoomerangBrother::BoomerangBrother()
{
	LoadAnimation();
	EntityTag = Tag::enemy;
	direction = -1;
	ColTag = Collision2DTag::FourSide;

	this->state = 0; 

	this->setRenderOrder(2);

	waittime = GetTickCount();
}

void BoomerangBrother::LoadAnimation()
{
	auto animations = AnimationManager::GetInstance();

	AddAnimation("Walk", animations->GetAnimation("ani-boomerang-brother-move"));
	AddAnimation("Attack", animations->GetAnimation("ani-boomerang-brother-attack"));
}

void BoomerangBrother::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->Position.x;
	top = this->Position.y;
	right = this->Position.x + WIDTH;
	bottom = this->Position.y + HEIGHT;
}

void BoomerangBrother::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;


if (die)
	{
		if (!(GetTickCount() - FlyDieTime_start > BOOMER_TIME_FLYDIE))
			vy = -BOOMER_FLYDIE_FORCE_VY * dt;
		vy += BOOMER_GRAVITY * dt;
	}


	switch (state) 
	{
	case 0:
		vx = MOVE_SPEED  ;
		if (GetTickCount() - waittime > CYCLE)
		{
			state = 1;
			waittime = GetTickCount();
		}
		break;

	case 1: 
		vx = -MOVE_SPEED ;
		if (GetTickCount() - waittime > CYCLE)
		{
			state = 2;
			waittime = GetTickCount();
		}
		break;
	case 2:
		vx = 0;
		if (GetTickCount() - waittime > WAIT)
		{
			this->Throw();
			state = 0;
			waittime = GetTickCount();
		}
		break;
	default:
		break;
	}
}

void BoomerangBrother::Render(Camera* camera)
{
	GameObject::Render(camera);

	std::string ani = "Walk";

	if (die)
		flipy = -1;

	animation_set[ani]->Render(RenderPosition.x, RenderPosition.y,this->Scale, direction, flipy);


}

void BoomerangBrother::Throw()
{
	ScenceManager::GetInstance()->getCurrentScence()->AddObject(new Boomerang(this->Position.x, this->Position.y, 1, 1));
}

void BoomerangBrother::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->EntityTag == Tag::player)
	{
		if (ny < 0)
		{
			this->die = true; 
			FlyDieTime_start = GetTickCount();
			this->ColTag = Collision2DTag::None;
		}
	}
}
