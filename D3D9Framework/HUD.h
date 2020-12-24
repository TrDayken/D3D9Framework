#ifndef __HUD_H__
#define __HUD_H__

#include "Global_Variable.h"
#include "UIObject.h"


class HUD : UIObject
{
	void Update(DWORD dt); 

	void Render(); 
};

#endif