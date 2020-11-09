#include "Mario.h"

Mario::Mario(float x, float y)
{
	AnimationLoad();
	
	this->start_x = x; 
	this->start_y = y;

	this->x = x;
	this->y = y;


	StateofMario.push_back(new SmallMario());
	StateofMario.push_back(new BigMario());
	StateofMario.push_back(new FireMario());
	StateofMario.push_back(new RacoonMario());

	CurrentMario = StateofMario[1];

	CurrentMario->setPosition(x, y);
}

void Mario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects)
{
	if (CurrentMario->getLevel() != DONTCHANGE) SwitchMario(CurrentMario->getLevel());

	//call update on specific mario
	CurrentMario->Update(dt, collision_objects);
	//after update need to reupdate the mariostate position to mario to render camera;
	this->setPosition(CurrentMario->getX(), CurrentMario->getY());

}

//void Mario::Render()
//{
//	animation_set.at(1)->Render(this->start_x,this->start_y);
//}

void Mario::Render(Camera* camera)
{
	CurrentMario->Render(camera);
}

void Mario::OnOverLap(GameObject* obj)
{
	CurrentMario->OnOverLap(obj);
}

void Mario::SetState(int state)
{
}

MarioModel* Mario::GetCurrentMario()
{
	return this->CurrentMario;
}

void Mario::Reset()
{
}

void Mario::AnimationLoad()
{
	//LPANIMATION ani = AnimationManager::GetInstance()->GetAnimation("ani-small-mario-walk");
	//animation_set.push_back(ani);
	//ani = AnimationManager::GetInstance()->GetAnimation("ani-big-mario-walk");
	//animation_set.push_back(ani);
}

void Mario::SwitchMario(int level)
{
	this->y = 100;
	levelmario = level;
	CurrentMario->SetLevel(DONTCHANGE);
	CurrentMario = StateofMario[levelmario];
	CurrentMario->SetPosition(this->x, this->y);
}

void Mario::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	this->CurrentMario->GetBoundingBox(left, top, right, bottom);
}
