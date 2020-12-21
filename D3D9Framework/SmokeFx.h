#pragma once
#include "AbstractFXObject.h"

class SmokeFx :
	public AbstractFXObject
{
private:
	DWORD Animation_created;

	void LoadAnimation(); 

public:

	SmokeFx(); 

	void Render(Camera* camera); 
};

