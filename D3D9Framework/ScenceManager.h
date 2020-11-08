#ifndef __SCENCEMANAGER_H__
#define __SCENCEMANAGER_H__

#include "Scence.h"

class ScenceManager
{
	static ScenceManager* _instance;

	Scence* currentscence;
public:

	void AddScence(Scence* scence);

	Scence* getCurrentScence();

	static ScenceManager* GetInstance();
};

#endif // !__SCENCEMANAGER_H__


