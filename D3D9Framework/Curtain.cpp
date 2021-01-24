#include "Curtain.h"

#define SPEED_CURTAIN 0.2f
#define MAX_CURTAIN 600.00f

Curtain::Curtain()
{
	auto animation = AnimationManager::GetInstance();

	this->AddAnimation("curtain", animation->GetAnimation("ani-full-curtain-"));

	this->renderorder = 6;
}

void Curtain::LoadAnimation()
{
}

void Curtain::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["curtain"]->Render(RenderPosition.x, RenderPosition.y);
}

void Curtain::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;

	dy = -SPEED_CURTAIN * dt; 

	if (this->Position.y + dy >= -MAX_CURTAIN)
		this->Position = D3DXVECTOR2(this->Position.x, this->Position.y + dy);
	else this->Position = D3DXVECTOR2(this->Position.x, -MAX_CURTAIN);
}
