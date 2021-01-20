#include "FallingPlatform.h"

FallingPlatform::FallingPlatform()
{
	stepedon = false;

	this->LoadAnimation();

	this->ColTag = Collision2DTag::FourSide;

	this->EntityTag = Tag::unstableplatform;
}

void FallingPlatform::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Default", animation->GetAnimation("ani-platform"));
}

void FallingPlatform::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->Position.x;
	top = this->Position.y;
	right = this->Position.x + 48 * 3;
	bottom = this->Position.y + 44;
}

void FallingPlatform::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->EntityTag == Tag::player);
	{
		stepedon = true;
	}
}

void FallingPlatform::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	this->Position.x += dx;
	this->Position.y += dy;

	if (stepedon)
	{
		this->vx = 0;
		this->vy += 0.0002f * dt;

		if (vy > 0.15)
			vy = 0.15;
	}
}

void FallingPlatform::Render(Camera* camera)
{
	GameObject::Render(camera); 

	animation_set["Default"]->Render(RenderPosition.x, RenderPosition.y);

}


