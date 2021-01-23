#include "MarioDeathFx.h"

void MarioDeathFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-coin"));
}

MarioDeathFx::MarioDeathFx()
{
	LoadAnimation();

	ANIMATIONTIME = 3000;

	Bounce_start = GetTickCount();

	this->setRenderOrder(5);
}

void MarioDeathFx::Render(Camera* camera)
{
	AbstractFXObject::Render(camera);

	animation_set["Fx"]->Render(RenderPosition.x, RenderPosition.y);
}

void MarioDeathFx::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;

	if (!(GetTickCount() - Bounce_start > MARIO_TIME))
		vy = -MARIO_BOUNCE;
	vy += MARIO_GRAVITY * dt;
}
