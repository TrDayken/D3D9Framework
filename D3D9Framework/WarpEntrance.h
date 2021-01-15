#pragma once
#include "GameObject.h"

enum class WarpDirection
{
	up,
	down,
	left,
	right
};


class WarpEntrance :
	public GameObject
{
private:
	WarpDirection dir;
public:
	WarpEntrance();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnOverLap(GameObject* obj);

	void setWarpDirection(WarpDirection dir);
	WarpDirection getWarpDirection();

	void Render(Camera* camera);

	int getKeyDirection();
};

