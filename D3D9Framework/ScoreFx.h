#pragma once
#include "AbstractFXObject.h"

#define FLOAT_SPEED 0.45f
#define DRAG 0.0009f

class ScoreFx :
	public AbstractFXObject
{
private: 

	int level; 

	Sprite* score[9];

	float speed;

	void LoadAnimation();

public: 
	ScoreFx();

	void setLevel(int level); 

	void Render(Camera* camera);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

};

