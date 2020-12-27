#include "PMetter.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "ScenceManager.h"
#include "PlayScence.h"

void PMetter::LoadAnimation()
{
	AddAnimation("P-blink", AnimationManager::GetInstance()->GetAnimation("ani-p-icon"));

	ArrowOn = SpriteManager::GetInstance()->GetSprite("spr-arrow-0"); 
	ArrowOff = SpriteManager::GetInstance()->GetSprite("spr-arrow-1");
	P_On = SpriteManager::GetInstance()->GetSprite("spr-p-icon-0");
	P_Off = SpriteManager::GetInstance()->GetSprite("spr-p-icon-1");
}

PMetter::PMetter()
{
	this->LoadAnimation();
}

PMetter::~PMetter()
{
}

void PMetter::Update(DWORD dt)
{
}

void PMetter::Render()
{
	int x = 0;
	for (int i = 0; i < 6; i++)
	{
		ArrowOff->Draw(StaticPosition.x + x, StaticPosition.y);
		x += ArrowOff->getSpriteWidth();
	}
	P_Off->Draw(StaticPosition.x + x, StaticPosition.y);

	x = 0;

	int level = Global_Variable::GetInstance()->getPmetter();

	int arrowlevel = level;

	if (arrowlevel == 7) arrowlevel = 6;

	for (int i = 0; i < arrowlevel ; i++)
	{
		ArrowOn->Draw(StaticPosition.x + x, StaticPosition.y); 
		x += ArrowOn->getSpriteWidth();
	}
	if (level == 7)
		animation_set["P-blink"]->Render(StaticPosition.x + x, StaticPosition.y);
}
