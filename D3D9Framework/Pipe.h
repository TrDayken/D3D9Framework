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
public:
	Pipe(); 

	void AddAnimation();

	void SetTile(int x, int y);

	void SetPipeDirection(PipeDirection dir);

	void Render(Camera* camera);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

