#include "CoinFx.h"
#include "ScenceManager.h"

void CoinFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-coin"));
}

CoinFx::CoinFx()
{
	LoadAnimation();

	ANIMATIONTIME = 650;

	Bounce_start = GetTickCount(); 
}

void CoinFx::Render(Camera* camera)
{
	AbstractFXObject::Render(camera); 

	animation_set["Fx"]->Render(RenderPosition.x, RenderPosition.y);
}

void CoinFx::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt); 

	this->Position.x += dx;
	this->Position.y += dy;

	if(!(GetTickCount() - Bounce_start > COIN_TIME))
		vy = -COIN_BOUNCE; 
	vy += COIN_GRAVITY * dt; 

	if (GetTickCount() - Animation_created > ANIMATIONTIME)
	{
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
	}
}
