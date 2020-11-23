#include "Mario.h"

Mario::Mario(float x, float y)
{
	//load animation
	AnimationLoad();
	
	//initial position for mario
	this->start_x = x; 
	this->start_y = y;

	this->x = x;
	this->y = y;

	//create every mario in the list
	StateofMario.push_back(new SmallMario());
	StateofMario.push_back(new BigMario());
	StateofMario.push_back(new FireMario());
	StateofMario.push_back(new RacoonMario());

	//initial current mario = BIG
	CurrentMario = StateofMario[BIG];

	//CurrentMario->setPosition(x, y);
}

void Mario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects)
{
	if (CurrentMario->getChangetoLevel() != DONTCHANGE) SwitchMario(CurrentMario->getChangetoLevel());

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
	//when reconize changes determine if the current state is mario small or not;
	//fix the previous mario change level to DONTCHANGE
	//set the right position big to small += y small to big -= y

	// check the current mario position
	if (CurrentMario->getCurrentLevel() == SMALL);
	//get the desire mario changetolevel
	int changetolevel = CurrentMario->getChangetoLevel();

	//preconfiguration on the premario
	CurrentMario->SetChangetoLevel(DONTCHANGE);
	//change the mario to the desire mario
	CurrentMario = StateofMario[changetolevel];
	//update on the changed mario => prevent AABB overlaping
	CurrentMario->SetPosition(this->x, this->y);

	//delete &changetolevel;
}

void Mario::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	this->CurrentMario->GetBoundingBox(left, top, right, bottom);
}
