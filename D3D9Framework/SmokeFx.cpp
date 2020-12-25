#include "SmokeFx.h"
#include "ScenceManager.h"
#include "Game.h"

void SmokeFx::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance(); 

	//AddAnimation("Smokefx", animation->GetAnimation("ani-fireball-damaged"));
	AddAnimation("Smokefx", animation->GetAnimation("ani-fireball-damaged"));
}

SmokeFx::SmokeFx()
{
	LoadAnimation(); 

	ANIMATIONTIME = 400; 
}

void SmokeFx::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(startPosition.x, startPosition.y); 

	//Game::GetInstance()->GetFont()->RenderText("THE QUICK BROWN FOX", pos); 

	animation_set["Smokefx"]->Render(pos.x, pos.y); 
}

