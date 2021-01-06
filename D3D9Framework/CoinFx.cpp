#include "CoinFx.h"
#include "ScenceManager.h"
#include "FXObjectManager.h"

void CoinFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-coin"));
}

CoinFx::CoinFx()
{
	LoadAnimation();

	ANIMATIONTIME = 600;

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
		FXObjectManager::GetInstance()->CreateFx("score", this->Position);
		Global_Variable::GetInstance()->AddScore(100);
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
	}
}
