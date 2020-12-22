#include "FXObjectManager.h"
#include "ScenceManager.h"
#include "SmokeFx.h"

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
	else
		DebugOut(L"[ERROR] Cannot find Fx validation"); 

	ScenceManager::GetInstance()->getCurrentScence()->AddObject(fx); 
	fx->setStartPosition(start_positon); 

	return fx;
}
