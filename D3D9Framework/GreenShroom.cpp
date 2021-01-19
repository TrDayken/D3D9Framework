#include "GreenShroom.h"
#include "ScoreFx.h"
#include "FXObjectManager.h"
#include "ScenceManager.h"

GreenShroom::GreenShroom()
{
	this->LoadAnimation();
}

void GreenShroom::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Idle", animation->GetAnimation("ani-1-up-mushroom"));

}

void GreenShroom::OnOverLap(GameObject* obj)
{
	if (obj->EntityTag == Tag::player)
	{

		ScoreFx* score = static_cast<ScoreFx*>(FXObjectManager::GetInstance()->CreateFx("score", this->Position));
		score->setLevel(8);
		Global_Variable::GetInstance()->AddLife(1);
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
	}
}
