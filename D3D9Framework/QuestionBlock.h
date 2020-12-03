#ifndef __QUESTIONBLOCK_H__
#define __QUESTIONBLOCK_H__

#include "GameObject.h"
#include "Camera.h"

class QuestionBlock :
	public GameObject
{

public:
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera* camera);
};

#endif // !__QUESTIONBLOCK_H__
