#ifndef __COIN_H__
#define __COIN_H__

#include "GameObject.h"

#define COIN_BBOX_WIDTH		42
#define COIN_BBOX_HEIGHT	48

class Coin :
	public GameObject
{
	void LoadAnimation(); 
public:

	Coin(); 

	void Render(Camera* camera); 

	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif