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

	std::unordered_map<int, LPSPRITE> CardVisual;

	std::vector<int> cards;

public:

	HUD();

	~HUD();

	void Update(DWORD dt); 

	void Render(); 


};

#endif