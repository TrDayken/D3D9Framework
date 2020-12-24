#ifndef __HUD_H__
#define __HUD_H__

#include "Global_Variable.h"
#include "UIObject.h"
#include "PMetter.h"


class HUD : public UIObject
{
private:
	Vector2 world, life, score, coin, timer; 

	PMetter* metter; 

	LPSPRITE hud; 

public:

	HUD();

	~HUD();

	void Update(DWORD dt); 

	void Render(); 


};

#endif