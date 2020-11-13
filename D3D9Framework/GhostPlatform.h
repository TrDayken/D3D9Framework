#ifndef __GHOSTPLATFORM_H__
#define __GHOSTPLATFORM_H__

#include "GameObject.h"
#include "Camera.h"

class GhostPlatform :public GameObject
{

public:
	GhostPlatform();
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif // !__GHOSTPLATFORM_H__