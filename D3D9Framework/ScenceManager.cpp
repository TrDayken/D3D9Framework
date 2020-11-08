#include "ScenceManager.h"

ScenceManager* ScenceManager::_instance = NULL;

void ScenceManager::AddScence(Scence* scence)
{
	currentscence = scence;
}

Scence* ScenceManager::getCurrentScence()
{
	return currentscence;
}

ScenceManager* ScenceManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new ScenceManager();
	return _instance;
}
