#ifndef __BRICK_H__
#define __BRICK_H__

#include "GameObject.h"

#define BRICK_BBOX_WIDTH 48
#define BRICK_BBOX_HEIGHT 48

class Brick
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif
