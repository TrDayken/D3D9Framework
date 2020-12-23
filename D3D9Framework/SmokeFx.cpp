#include "SmokeFx.h"
#include "ScenceManager.h"

void SmokeFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance(); 

	AddAnimation("Smokefx", animation->GetAnimation("ani-brick-debris"));
}

SmokeFx::SmokeFx()
{
	LoadAnimation(); 

	ANIMATIONTIME = 400; 
}

void SmokeFx::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(startPosition.x, startPosition.y); 

	animation_set["Smokefx"]->Render(pos.x, pos.y); 
}

