#include "Coin.h"
#include "ScenceManager.h"

void Coin::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	this->AddAnimation("coin", animation->GetAnimation("ani-coin"));
}

Coin::Coin()
{
	this->LoadAnimation(); 

	ColTag = Collision2DTag::None;

	EntityTag = Tag::coin; 
}

void Coin::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["coin"]->Render(RenderPosition.x, RenderPosition.y);
}

void Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + COIN_BBOX_WIDTH;
	b = this->Position.y + COIN_BBOX_HEIGHT;
}

void Coin::OnOverLap(GameObject* obj)
{
	if (obj->EntityTag == Tag::player)
	{
		Global_Variable::GetInstance()->AddCoin(1);
		Global_Variable::GetInstance()->AddScore(50);
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
	}
}

void Coin::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	std::vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	CalcPotentialCollisions(coObjects,coEvents);
}
