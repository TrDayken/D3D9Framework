#include "MushroomFx.h"

void MushroomFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-goal-mushroom"));
}

MushroomFx::MushroomFx()
{
	LoadAnimation();

	ANIMATIONTIME = 600;

	this->setRenderOrder(5);
}

void MushroomFx::Render(Camera* camera)
{
	AbstractFXObject::Render(camera);

	animation_set["Fx"]->Render(RenderPosition.x, RenderPosition.y);
}

void MushroomFx::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;

	vy = -FLY_SPEED;
}
