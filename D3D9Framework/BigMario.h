#ifndef __BIGMARIO_H__
#define __BIGMARIO_H__

#include <vector>
#include <d3dx9.h>

#include "MarioModel.h"
#include "Camera.h"

#define MARIO_BIG_BBOX_WIDTH				42
#define MARIO_BIG_BBOX_HEIGHT				80
#define MARIO_BIG_BBOX_HEIGHT_CROUCH		54

class BigMario : public MarioModel
{
public:
	BigMario();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
	void LoadAnimation();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void BigMarioRunandWalkState();
};

#endif