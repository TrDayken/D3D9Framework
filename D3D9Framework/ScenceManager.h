#ifndef __SCENCEMANAGER_H__
#define __SCENCEMANAGER_H__

#include "Scence.h"
//#include "PlayScence.h"
#include "AnimationManager.h"
#include "SpriteManager.h"
#include "Textures.h"
#include "Utils.h"



class ScenceManager
{
	static ScenceManager* _instance;

	Scence* currentscence;
public:

	void AddScence(Scence* scence);

	void LoadScenceFromXML(const char* FilePath);

	Scence* getCurrentScence();

	static ScenceManager* GetInstance();
};

#endif // !__SCENCEMANAGER_H__


