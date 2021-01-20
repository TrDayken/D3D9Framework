#include "HitFx.h"

void HitFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-enemy-damaged"));
}

HitFx::HitFx()
{
	LoadAnimation();
	
	ANIMATIONTIME = 100;

	this->setRenderOrder(5);
}

void HitFx::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(Position.x, Position.y);

	animation_set["Fx"]->Render(pos.x, pos.y);
}
