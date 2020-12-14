#include "QuestionBlock.h"
#include "AnimationManager.h"
#include "ScenceManager.h"

QuestionBlock::QuestionBlock()
{
	this->LoadAnimation();

	this->EntityTag = Tag::questionblock;

	this->Deflected = false;

	this->isBounce = false;

	this->relativePosition = VectorZero;
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

		DebugOut(L"[INFO] start bounce \n");
	}
}

void QuestionBlock::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (isBounce)
	{
		if(!(GetTickCount() - Start_Bounce_Time > BOUNCE_TIME))
			this->relativePosition.y -= BOUNCE_VEL * dt;			
	}
}

void QuestionBlock::Render(Camera* camera)
{
	//[TODO] relative position 
	Vector2 pos = camera->toCameraPosistion(this->Position.x, this->Position.y);

	Vector2 relativerenderpos = pos + relativePosition;
	//Vector2 relativepos = pos;
	animation_set["Active"]->Render(relativerenderpos.x, relativerenderpos.y);

	//AnimationManager::GetInstance()->GetAnimation("ani-coin")->Render(pos.x, pos.y);

	RenderBoundingBox(camera);
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
