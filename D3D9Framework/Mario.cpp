#include "Mario.h"

Mario::Mario(float x, float y)
{
	//load animation
	AnimationLoad();
	
	//initial position for mario
	this->start_x = x; 
	this->start_y = y;

	this->Position.x = x;
	this->Position.y = y;

	this->Life = 4; 

	this->Coin = 0; 

	this->Score = 0; 

	this->Combo = 0; 

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
	this->Life = 4; 

	this->Coin = 0; 

	this->Score = 0; 
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
	int prechangelevel = CurrentMario->getCurrentLevel();
	int changetolevel = CurrentMario->getChangetoLevel();

	//preconfiguration on the premario
	CurrentMario->SetChangetoLevel(DONTCHANGE);
	//change the mario to the desire mario
	CurrentMario = StateofMario[changetolevel];
	//update on the changed mario => prevent AABB overlaping
	CurrentMario->SetPosition(this->Position.x, this->Position.y);

	CurrentMario->setDirection(StateofMario[prechangelevel]->getDirection());
	//delete &changetolevel;
}

void Mario::setCamera(Camera* camera)
{
	this->camera = camera;
}

int Mario::getPmetter()
{
	return this->CurrentMario->getPmetter();
}

void Mario::setCoin(int coin)
{
	this->Coin = coin;
}

int Mario::getCoin()
{
	return this->Coin;
}

void Mario::setLife(int life)
{
	this->Life = life; 
}

int Mario::getLife()
{
	return this->Life;
}

void Mario::setScore(long score)
{
	this->Score = score; 
}

long Mario::getScore()
{
	return this->Score;
}

void Mario::ResetCombo()
{
	this->Combo = 0; 
}

void Mario::ComboUp()
{
	this->Combo++; 
}

int Mario::getCombo()
{
	return this->Combo;
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	this->CurrentMario->GetBoundingBox(left, top, right, bottom);
}
