#pragma once
#include "AbstractFXObject.h"

class SmokeFx :
	public AbstractFXObject
{
private:

	void LoadAnimation(); 

public:

	SmokeFx(); 

	void Render(Camera* camera); 
};

