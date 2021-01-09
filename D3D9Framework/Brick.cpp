#include "Brick.h"
#include "AnimationManager.h"

Brick::Brick()
{
	LoadAnimation();

	ColTag = Collision2DTag::FourSide;

	EntityTag = Tag::platform;
}

void Brick::Render(Camera* camera)
{
	GameObject::Render(camera); 

	animation_set["GoldenBrick"]->Render(RenderPosition.x, RenderPosition.y); 

	//RenderBoundingBox(camera);
}

void Brick::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	this->AddAnimation("GoldenBrick", animation->GetAnimation("ani-brick"));
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + BRICK_BBOX_WIDTH;
	b = this->Position.y + BRICK_BBOX_HEIGHT;
}

void Brick::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
}
