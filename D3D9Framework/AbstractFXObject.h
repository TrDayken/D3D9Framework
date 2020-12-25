#pragma once
#include "GameObject.h"

class AbstractFXObject : public GameObject
{
protected:

	Vector2 startPosition; 

	DWORD Animation_created;

	DWORD ANIMATIONTIME;

	Vector2 Force;

public:

	AbstractFXObject(); 

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);

	void setStartPosition(Vector2 pos); 

	virtual void Render(Camera* camera); 

	void setForce(Vector2 force);

};

