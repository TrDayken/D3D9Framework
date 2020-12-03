#include "QuestionBlock.h"
#include "AnimationManager.h"

QuestionBlock::QuestionBlock()
{
	this->LoadAnimation();

	this->Deflected = 0;
}

QuestionBlock::~QuestionBlock()
{
}

void QuestionBlock::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	//theres one more 
	//check if the question block had already deactivated or not
	//if none quantity -- 
	//poop out the item which this object hold;

	//if deflected then pass => nothing will happen


	if (obj->EntityTag == Tag::player)
	{

	}
}

void QuestionBlock::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(this->x, this->y);


}

void QuestionBlock::LoadAnimation()
{
	auto animationmanager = AnimationManager::GetInstance();

	AddAnimation("Active_Question_Block", animationmanager->GetAnimation("ani-question-block"));
	AddAnimation("Empty_Question_Block", animationmanager->GetAnimation("ani-empty-block"));
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
