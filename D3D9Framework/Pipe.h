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

	float lock_x;
	float lock_y;

	bool isstatic, isfollow, scroll_x, scroll_y;

	int camt, caml, camr, camb;

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

	void setLockx(float x);
	void setLocky(float y);

	float getLockx();
	float getLocky();

	void setIsstatic(bool is);
	void setIsfollow(bool is);
	void setScrollx(bool is);
	void setScrolly(bool is);

	bool getIsstatic();
	bool getIsfollow();
	bool getScrollx();
	bool getScrolly();

	void setCamProp(int camt, int caml, int camr, int camb);

	int getCamt();
	int getCaml();
	int getCamr();
	int getCamb();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnOverLap(GameObject* obj);
};

