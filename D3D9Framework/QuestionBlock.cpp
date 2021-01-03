#include "QuestionBlock.h"
#include "AnimationManager.h"
#include "ScenceManager.h"
#include "RedMushroomPowerUps.h"
#include "RaccoonPowerUps.h"
#include "FXObjectManager.h"

QuestionBlock::QuestionBlock()
{
	this->LoadAnimation();

	this->EntityTag = Tag::questionblock;

	this->Deflected = false;

	this->isBounce = false;

	this->BounceState = 0; 

	this->ColTag = Collision2DTag::FourSide;

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

	//[Critical]
	//when bounce state = 1 or 2 ; 
	// detect as if there are an enemy above the block when mairo hit it?
	if (!Deflected)
	{
		if (obj->EntityTag == Tag::player)
		{
			this->isBounce = true;
			this->Start_Bounce_Time = GetTickCount();
			this->BounceState = 1;
			DebugOut(L"[INFO] start bounce \n");

			switch (InBlockItem)
			{
			case Item::RedShroom:
			{
				GameObject* mush = new RedMushroomPowerUps(); 

				mush->setPosition(this->Position.x, this->Position.y - 49);
				ScenceManager::GetInstance()->getCurrentScence()->AddObject(mush);
			}
				break;
			case Item::RaccoonLeaf:
			{
				GameObject* leaf = new RaccoonPowerUps();

				leaf->setPosition(this->Position.x, this->Position.y);
				ScenceManager::GetInstance()->getCurrentScence()->AddObject(leaf);
			}
				break;
			case Item::FireFlower:
				break;
			case Item::GreenShroom:
				break;
			case Item::Coin:
				FXObjectManager::GetInstance()->CreateFx("coin", this->Position);
				break;
			default:
				break;
			}

			this->Quantity--;

			if (this->Quantity <= 0)
				this->Deflected = true;
		}
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

	std::string ani = "Active";

	if (Deflected)
		ani = "Empty";
	
	animation_set[ani]->Render(RenderPosition.x, RenderPosition.y);

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

void QuestionBlock::SetDeflected(bool isdeflected)
{
	this->Deflected = isdeflected; 
}

bool QuestionBlock::GetDeflected()
{
	return this->Deflected;
}
