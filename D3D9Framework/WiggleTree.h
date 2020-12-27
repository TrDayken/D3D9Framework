#ifndef __WIGGLETREE_H__
#define __WIGGLETREE_H__

#include "GameObject.h"

class WiggleTree :
	public GameObject
{
public:

	WiggleTree();

	void LoadAnimation();

	void Render(Camera* camera);

	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

#endif