#include "DebrisFx.h"

void DebrisFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation("Fx", animation->GetAnimation("ani-brick-debris"));

}

DebrisFx::DebrisFx()
{
	LoadAnimation();

	ANIMATIONTIME = 1000;

	Bounce_start = GetTickCount(); 

	this->setRenderOrder(5);
}

void DebrisFx::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(Position.x, Position.y);

	animation_set["Fx"]->Render(pos.x, pos.y);
}

void DebrisFx::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	AbstractFXObject::Update(dt, coObjects); 

	this->Position.x += dx;
	this->Position.y += dy;

	if (!(GetTickCount() - Bounce_start > DEBRIS_TIME))
	{
		vx = Force.x;
		vy = Force.y;
	}
	vy += DEBRIS_GRAVITY * dt;
}


