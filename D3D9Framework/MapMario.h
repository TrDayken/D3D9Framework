#pragma once
#include "GameObject.h"
#include "NodeMap.h"
#include <dinput.h>

#define MARIO_SPEED 0.45f

class MapMario :
	public GameObject
{
private:
	void LoadAnimation();

	int currentNode; 

	Vector2 des;
	Vector2 predes;
	Vector2 distance;

	bool ismovingx, ismovingy;

	NodeMap* map;

public:
	MapMario();

	~MapMario();

	void setMap(NodeMap* map);

	NodeMap* getMap();

	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects = NULL);

	virtual void Render(Camera* camera);

	void OnKeyDown(int KeyCode);
};

