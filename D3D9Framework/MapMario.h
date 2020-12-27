#pragma once
#include "GameObject.h"

#define MARIO_SPEED 0.45f

class MapMario :
	public GameObject
{
private:
	void LoadAnimation();

	int currentNode; 
	Vector2 destination;
	bool ismoving;
public:
	MapMario();
	~MapMario();

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects = NULL);

	virtual void Render(Camera* camera);

	void OnKeyDown(int KeyCode);
};

