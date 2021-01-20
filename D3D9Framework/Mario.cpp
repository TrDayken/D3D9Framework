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

	//create every mario in the list
	StateofMario.push_back(new SmallMario());
	StateofMario.push_back(new BigMario());
	StateofMario.push_back(new FireMario());
	StateofMario.push_back(new RacoonMario());

	//initial current mario = BIG
	CurrentMario = StateofMario[Global_Variable::GetInstance()->getMarioLevel()];

	//CurrentMario->setPosition(x, y);
	this->ColTag = Collision2DTag::None;
	this->EntityTag = Tag::player;
}

void Mario::Unload()
{
	for (int i = 0; (unsigned)i < StateofMario.size(); i++)
		delete StateofMario[i];

	CurrentMario = NULL;
	
}

void Mario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects)
{
	if (CurrentMario->getChangetoLevel() != DONTCHANGE) 
		SwitchMario(CurrentMario->getChangetoLevel());

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
	//get the desire mario changetolevel
	int prechangelevel = CurrentMario->getCurrentLevel();
	int changetolevel = CurrentMario->getChangetoLevel();

	//preconfiguration on the premario
	CurrentMario->SetChangetoLevel(DONTCHANGE);

	float offset = MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;

	if (changetolevel == SMALL && prechangelevel != SMALL)
	{
		StateofMario[changetolevel]->SetPosition(this->Position.x, this->Position.y + offset);
	}
	else if (changetolevel != SMALL && prechangelevel == SMALL)
	{
		StateofMario[changetolevel]->SetPosition(this->Position.x, this->Position.y - offset);
	}
	else
	{
		StateofMario[changetolevel]->SetPosition(this->Position.x, this->Position.y);
	}

	StateofMario[changetolevel]->setDirection(CurrentMario->getDirection());

	StateofMario[changetolevel]->setSpeed(CurrentMario->getVx(), CurrentMario->getVy()); 

	StateofMario[changetolevel]->SetState(CurrentMario->getState());

	StateofMario[changetolevel]->setJumpstate(CurrentMario->getJumpState());

	StateofMario[changetolevel]->setMovestate(CurrentMario->getMoveState());

	StateofMario[changetolevel]->setInvincible(CurrentMario->getInvincible());

	StateofMario[changetolevel]->setInvincible_Time(CurrentMario->getInvincible_Time());

	StateofMario[changetolevel]->setHold(CurrentMario->getHold());

	Global_Variable::GetInstance()->setMarioLevel(changetolevel);

	//change the mario to the desire mario
	CurrentMario = StateofMario[changetolevel];

}

void Mario::setCamera(Camera* camera)
{
	this->camera = camera;
}

int Mario::getPmetter()
{
	return this->CurrentMario->getPmetter();
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	this->CurrentMario->GetBoundingBox(left, top, right, bottom);
}
