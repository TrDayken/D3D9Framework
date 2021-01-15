#include "Brick.h"
#include "AnimationManager.h"
#include "FXObjectManager.h"
#include "ScenceManager.h"
#include "Global_Variable.h"

Brick::Brick()
{
	LoadAnimation();

	ColTag = Collision2DTag::FourSide;

	EntityTag = Tag::brick;

	this->state = BRICK_STATE;
}

void Brick::Render(Camera* camera)
{
	GameObject::Render(camera); 

	std::string ani = "GoldenBrick";

	if (state == COIN_STATE)
		ani = "PTime";

	animation_set[ani]->Render(RenderPosition.x, RenderPosition.y); 

	//RenderBoundingBox(camera);
}

void Brick::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	this->AddAnimation("GoldenBrick", animation->GetAnimation("ani-brick"));
	this->AddAnimation("PTime", animation->GetAnimation("ani-idle-coin"));

}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + BRICK_BBOX_WIDTH;
	b = this->Position.y + BRICK_BBOX_HEIGHT;
}

void Brick::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->EntityTag == Tag::player || obj->EntityTag == Tag::shell)
	{
		this->Explode();
	}
}

void Brick::OnOverLap(GameObject* obj)
{
	if (obj->EntityTag == Tag::tail && state == BRICK_STATE)
	{
		this->Explode();
	}

	if (obj->EntityTag == Tag::player && state == COIN_STATE)
	{
		Global_Variable::GetInstance()->AddCoin(1);
		Global_Variable::GetInstance()->AddScore(50);
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
	}
}

void Brick::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (Global_Variable::GetInstance()->isPtimeUp())
	{
		this->state = COIN_STATE;
		ColTag = Collision2DTag::None;

	}
	else
	{
		this->state = BRICK_STATE;
		ColTag = Collision2DTag::FourSide;

	}
}

void Brick::Explode()
{
	const float velx[4] = { +0.15f, +0.20f, -0.20f, -0.15f };
	const float vely[4] = { -0.30f, -0.60f, -0.60f, -0.30f };

	for (int i = 0; i < 4; i++)
	{
		auto fx = FXObjectManager::GetInstance()->CreateFx("debris", this->Position);
		fx->setForce(Vector2(velx[i] * 1.25f, vely[i] * 1.25f));
	}
	ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
}
