#include "RedGoomba.h"

RedGoomba::RedGoomba()
{
	this->goomstate = GoombaState::flying;

	this->LoadAnimation();
}

void RedGoomba::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();


	AddAnimation(ANI_GOOMBA_WALK, animation->GetAnimation("ani-red-para-goomba-walk"));
	AddAnimation(ANI_GOOMBA_DIE, animation->GetAnimation("ani-red-goomba-die"));
	AddAnimation(ANI_GOOMBA_FLY, animation->GetAnimation("ani-red-para-goomba-fly"));

}
