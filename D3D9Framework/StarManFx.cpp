#include "StarManFx.h"

void StarManfx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-goal-star"));
}

StarManfx::StarManfx()
{
	LoadAnimation();

	ANIMATIONTIME = 600;

	this->setRenderOrder(5);
}

void StarManfx::Render(Camera* camera)
{
	AbstractFXObject::Render(camera);

	animation_set["Fx"]->Render(RenderPosition.x, RenderPosition.y);
}

void StarManfx::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;

	vy = -FLY_SPEED;
}
