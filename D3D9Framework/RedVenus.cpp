#include "RedVenus.h"
#include "AnimationManager.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include "VenusFireShoot.h"


void RedVenus::ShootFireBall()
{
	VenusFireShoot* fireshoot = new VenusFireShoot(this->Position.x, this->Position.y, -direction, (int)head);

	ScenceManager::GetInstance()->getCurrentScence()->AddObject(fireshoot);
}

RedVenus::RedVenus()
{
	this->LoadAnimation(); 

	hideTime_start = GetTickCount(); 

	this->EntityTag = Tag::plant;

	state = VenusState::hide;

	this->ColTag = Collision2DTag::FourSide; 

	this->setRenderOrder(2);
}

RedVenus::~RedVenus()
{
}

void RedVenus::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects); 

	this->Position.x += dx;
	this->Position.y += dy;

	switch (state)
	{
	case VenusState::hide:
	{
		distance = 0;
		if (GetTickCount() - hideTime_start > VENUS_HIDE)
		{
			state = VenusState::slideup;
		}
	}
	break;

	case VenusState::slideup:
	{
		vy = -VENUS_SPEED;
		distance += abs(vy * dt);
		if (distance > VENUS_HEIGHT)
		{
			vy = 0;
			distance = VENUS_HEIGHT;
			waitTime_start = GetTickCount();
			state = VenusState::idle;
		}
	}
		break; 
	case VenusState::idle:
	{
		Vector2 playerposition; 
		((PlayScence*)ScenceManager::GetInstance()->getCurrentScence())->GetPlayer()->getPosition(playerposition.x, playerposition.y); 
		
		if (playerposition.y > this->Position.y)
			head = VenusHead::down;
		else
			head = VenusHead::up;

		if (playerposition.x > this->Position.x)
			this->direction = -1;
		else
			this->direction = 1; 

		if (GetTickCount() - waitTime_start > VENUS_WAIT)
		{

			distance = 0; 
			state = VenusState::slidedown;

			ShootFireBall(); 
		}
	}
	break; 

	case VenusState::slidedown:
	{
		vy = VENUS_SPEED;
		distance += abs(vy * dt);
		if (distance > VENUS_HEIGHT)
		{
			vy = 0; 
			distance = VENUS_HEIGHT;
			hideTime_start = GetTickCount(); 
			state = VenusState::hide;
		}
	}
	break; 
	}


}

void RedVenus::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->EntityTag == Tag::projectile)
	{
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
	}
}

void RedVenus::Render(Camera* camera)
{
	GameObject::Render(camera);

	std::string ani; 

	if (state == VenusState::idle)
		ani += "Idle";

	if (head == VenusHead::up)
		ani += "HeadUp";
	else
		ani += "HeadDown"; 

	//RenderBoundingBox(camera);

	animation_set[ani]->Render(RenderPosition.x, RenderPosition.y, this->Scale, direction);
}

void RedVenus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x; 
	t = this->Position.y;
	r = this->Position.x + VENUS_WIDTH;
	b = this->Position.y + VENUS_HEIGHT;
}

void RedVenus::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("HeadUp", animation->GetAnimation("ani-red-venus-fire-trap-headup"));
	AddAnimation("HeadDown", animation->GetAnimation("ani-red-venus-fire-trap-headdown"));

	AddAnimation("IdleHeadUp", animation->GetAnimation("ani-red-venus-fire-trap-headup-idle"));
	AddAnimation("IdleHeadDown", animation->GetAnimation("ani-red-venus-fire-trap-headdown-idle"));
}


