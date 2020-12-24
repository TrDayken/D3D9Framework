#ifndef __PMETTER_H__
#define __PMETTER_H__


#include "UIObject.h"
#include "Sprite.h"

class PMetter :
	public UIObject
{
private: 
	void LoadAnimation(); 

	LPSPRITE ArrowOn, ArrowOff, P_On, P_Off;
public:
	PMetter(); 
	~PMetter(); 

	void Update(DWORD dt);

	void Render(); 
};

#endif