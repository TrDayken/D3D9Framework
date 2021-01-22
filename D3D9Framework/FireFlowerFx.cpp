#include "FireFlowerFx.h"

void FireFlowerFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-goal-flower"));
}

FireFlowerFx::FireFlowerFx()
{
	LoadAnimation();

	ANIMATIONTIME = 600;

	this->setRenderOrder(5);
}

void FireFlowerFx::Render(Camera* camera)
{
	AbstractFXObject::Render(camera);

	animation_set["Fx"]->Render(RenderPosition.x, RenderPosition.y);
}

void FireFlowerFx::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;

	vy = -FLY_SPEED;
}
