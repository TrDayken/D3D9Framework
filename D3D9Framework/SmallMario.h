#ifndef __SMALLMARIO_H__
#define __SMALLMARIO_H__

#include "MarioModel.h"

class SmallMario : public MarioModel
{
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#endif