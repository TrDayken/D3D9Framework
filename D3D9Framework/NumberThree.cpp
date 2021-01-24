#include "NumberThree.h"

NumberThree::NumberThree()
{
	auto animation = AnimationManager::GetInstance();

	this->AddAnimation("three", animation->GetAnimation("ani-three"));

	this->Position =  Vector2(350, 275);

	this->renderorder = 4;
}

void NumberThree::LoadAnimation()
{
}

void NumberThree::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["three"]->Render(RenderPosition.x, RenderPosition.y);
}

void NumberThree::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}
