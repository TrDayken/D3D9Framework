#pragma once
#include "GameObject.h"

class AbstractFXObject : public GameObject
{
protected:

	Vector2 startPosition; 

	DWORD Animation_created;

	DWORD ANIMATIONTIME;

public:

	AbstractFXObject(); 

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);

	void setStartPosition(Vector2 pos); 

};

