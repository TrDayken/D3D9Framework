#ifndef __INVISIBLEBRICK_H__
#define __INVISIBLEBRICK_H__

#include "GameObject.h"
#include "AnimationManager.h"
#include "Camera.h"

#define BRICK_BBOX_WIDTH 48
#define BRICK_BBOX_HEIGHT 48

class InvisibleBrick: public GameObject
{
public:

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif

