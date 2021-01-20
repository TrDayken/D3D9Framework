#pragma once
#include "GameObject.h"

enum class Direction
{
	left,
	right
};

class FallingPlatform :
	public GameObject
{

	bool stepedon;
public:

	FallingPlatform();

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render(Camera* camera);

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

