#include "FakeGoldenBlock.h"

FakeGoldenBlock::FakeGoldenBlock() : QuestionBlock()
{
	this->LoadAnimation();
}

void FakeGoldenBlock::LoadAnimation()
{
	auto animationmanager = AnimationManager::GetInstance();

	AddAnimation("Active", animationmanager->GetAnimation("ani-brick"));
	AddAnimation("Empty", animationmanager->GetAnimation("ani-empty-block"));
}
