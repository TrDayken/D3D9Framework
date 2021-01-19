#include "GreenShroom.h"

GreenShroom::GreenShroom()
{
	this->LoadAnimation();
}

void GreenShroom::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Idle", animation->GetAnimation("ani-1-up-mushroom"));
}
