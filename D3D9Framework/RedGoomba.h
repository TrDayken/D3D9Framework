#pragma once
#include "Goomba.h"

#define ANI_GOOMBA_WALK		"ani-goomba-walk"
#define ANI_GOOMBA_DIE		"ani-goomba-die"
#define ANI_GOOMBA_IDLE		"ani-goomba-idle"
#define ANI_GOOMBA_FLY		"ani-red-para-goomba-fly"

class RedGoomba :
	public Goomba
{
private:
public:
	RedGoomba();

	void LoadAnimation();
};

