#include "FXObjectManager.h"
#include "ScenceManager.h"
#include "SmokeFx.h"
#include "HitFx.h"
#include "DebrisFx.h"
#include "CoinFx.h"
#include "ScoreFx.h"
#include "GrowUpFx.h"
#include "FireFlowerFx.h"
#include "StarManFx.h"
#include "MushroomFx.h"
#include "MarioDeathFx.h"

FXObjectManager* FXObjectManager::_instance = NULL; 

FXObjectManager* FXObjectManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new FXObjectManager();
	return _instance;
}

AbstractFXObject* FXObjectManager::CreateFx(std::string name, Vector2 start_positon)
{
	AbstractFXObject* fx = nullptr;

	if (name == "smoke")
		fx = new SmokeFx();
	else if (name == "hit")
		fx = new HitFx(); 
	else if (name == "grow")
	{
		fx = new GrowUpFx();
	}
	else if (name == "debris")
	{
		fx = new DebrisFx();
	}
	else if (name == "coin")
		fx = new CoinFx();
	else if (name == "score")
	{
		fx = new ScoreFx();
	}
	else if (name == "fireflower")
	{
		fx = new FireFlowerFx();
	}
	else if (name == "starman")
	{
		fx = new StarManfx();
	}
	else if (name == "mushroom")
	{
		fx = new MushroomFx();
	}
	else if (name == "death")
	{
		fx = new MarioDeathFx();
	}
	else
		DebugOut(L"[ERROR] Cannot find Fx validation"); 

	fx->setStartPosition(start_positon); 

	ScenceManager::GetInstance()->getCurrentScence()->AddObject(fx); 

	return fx;
}
