#include "SmokeFx.h"
#include "ScenceManager.h"
#include "Game.h"

void SmokeFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance(); 

	//AddAnimation("Smokefx", animation->GetAnimation("ani-fireball-damaged"));
	AddAnimation("Fx", animation->GetAnimation("ani-fireball-damaged"));
}

SmokeFx::SmokeFx()
{
	LoadAnimation(); 

	ANIMATIONTIME = 400; 

	this->setRenderOrder(5);
}

void SmokeFx::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(Position.x, Position.y);


	animation_set["Fx"]->Render(pos.x, pos.y); 
}

