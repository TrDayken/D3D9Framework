#ifndef __INVISIBLEBRICK_H__
#define __INVISIBLEBRICK_H__

#include "GameObject.h"
#include "Camera.h"

class InvisibleBrick: public GameObject
{
public:
	InvisibleBrick();

	virtual void Render(Camera* camera);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif

