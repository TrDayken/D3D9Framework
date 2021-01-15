#include "GreenVenus.h"

GreenVenus::GreenVenus()
{
	this->LoadAnimation();
}

void GreenVenus::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("HeadUp", animation->GetAnimation("ani-green-venus-fire-trap-headup"));
	AddAnimation("HeadDown", animation->GetAnimation("ani-green-venus-fire-trap-headdown"));

	AddAnimation("IdleHeadUp", animation->GetAnimation("ani-green-venus-fire-trap-headup-idle"));
	AddAnimation("IdleHeadDown", animation->GetAnimation("ani-green-venus-fire-trap-headdown-idle"));

}
