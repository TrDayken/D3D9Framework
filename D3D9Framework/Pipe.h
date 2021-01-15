#pragma once
#include "GameObject.h"

#define TILE_SIZE 48

enum class  PipeDirection
{
	Up,
	Down,
	Vertical
};

class Pipe :
	public GameObject
{
	int tile_X, tile_Y;

	LPSPRITE headTile, bodyTile;
	std::vector<LPSPRITE> rendervector; 

	PipeDirection dir; 

	float dest_x;
	float dest_y;

public:
	Pipe(); 

	void AddAnimation();

	void SetTile(int x, int y);

	void SetPipeDirection(PipeDirection dir);

	void Render(Camera* camera);

	void setDes_x(float x);
	float getDes_x();

	void setDes_y(float y);
	float getDes_y();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnOverLap(GameObject* obj);
};

