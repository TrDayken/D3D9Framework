#include "FXObjectManager.h"
#include "ScenceManager.h"

FXObjectManager* FXObjectManager::_instance = NULL; 

FXObjectManager* FXObjectManager::GetInstance()
{
	return nullptr;
}

AbstractFXObject* FXObjectManager::CreateFx(std::string name, Vector2 start_positon)
{
	return nullptr;
}
