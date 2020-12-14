#include "QuestionBlock.h"
#include "AnimationManager.h"
#include "ScenceManager.h"

QuestionBlock::QuestionBlock()
{
	this->LoadAnimation();

	this->EntityTag = Tag::questionblock;

	this->Deflected = false;

	this->isBounce = false;

	this->BounceState = 0; 

	//this->relativePosition = VectorZero;
}

QuestionBlock::~QuestionBlock()
{
}

void QuestionBlock::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	//theres one more problem
	//check if the question block had already deactivated or not
	//if none quantity -- 
	//poop out the item which this object hold;

	//if deflected then pass => nothing will happen

	//overall its will look like this:

	//if (!Deflected)
	//{
	//	if (obj->EntityTag == Tag::player)
	//	{
	//		if(ny > 0 ) ;
	//		shietouttheobjectit's holding;
	//	}
	//}

	if (obj->EntityTag == Tag::player)
	{
		this->isBounce = true;
		this->Start_Bounce_Time = GetTickCount();
		this->BounceState = 1; 
		DebugOut(L"[INFO] start bounce \n");
	}
}

void QuestionBlock::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (isBounce)
	{
		if (BounceState == 1)
		{
			//if (!(GetTickCount() - Start_Bounce_Time > BOUNCE_TIME))
			this->RelativePosition.y -= BOUNCE_VEL * dt;
			if (GetTickCount() - Start_Bounce_Time > BOUNCE_TIME)
			{
				Start_Bounce_Time = GetTickCount();
				BounceState = 2;
			}
		}
		else if (BounceState == 2)
		{
			this->RelativePosition.y += BOUNCE_VEL * dt;
			if (GetTickCount() - Start_Bounce_Time > BOUNCE_TIME)
			{
				this->RelativePosition.y = 0; 
				BounceState = 0;
			}
		}
	}
}

void QuestionBlock::Render(Camera* camera)
{
	GameObject::Render(camera); 

	animation_set["Active"]->Render(RenderPosition.x, RenderPosition.y);

	//RenderBoundingBox(camera);
}

void QuestionBlock::LoadAnimation()
{
	auto animationmanager = AnimationManager::GetInstance();

	AddAnimation("Active", animationmanager->GetAnimation("ani-question-block"));
	AddAnimation("Empty", animationmanager->GetAnimation("ani-empty-block"));
}

void QuestionBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->Position.x;
	top = this->Position.y;
	right = this->Position.x + 48;
	bottom = this->Position.y + 48;
}

void QuestionBlock::SetInBlockItem(Item inblockitem)
{
	this->InBlockItem = inblockitem;
}

Item QuestionBlock::GetInBlockItem()
{
	return this->InBlockItem;
}

void QuestionBlock::SetQuantity(int quantity)
{
	this->Quantity = quantity;
}

int QuestionBlock::GetQuantity()
{
	return this->Quantity;
}
