#ifndef __FXOBJECTMANAGER_H__
#define __FXOBJECTMANAGER_H__

#include "AbstractFXObject.h"

class FXObjectManager
{
	static FXObjectManager* _instance; 

public: 

	static FXObjectManager* GetInstance();

	AbstractFXObject* CreateFx(std::string name, Vector2 start_positon); 
};

#endif