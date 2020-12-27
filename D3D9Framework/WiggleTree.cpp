#include "WiggleTree.h"

WiggleTree::WiggleTree()
{
	LoadAnimation();

	ColTag = Collision2DTag::None;

	EntityTag = Tag::vanity;
}

void WiggleTree::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Default", animation->GetAnimation("ani-tree"));
}

void WiggleTree::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["Default"]->Render(RenderPosition.x, RenderPosition.y);
}

void WiggleTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
