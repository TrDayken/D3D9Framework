#ifndef __HUD_H__
#define __HUD_H__

#include "Global_Variable.h"

class HUD
{
	//on screen position rendering the HUD
	Vector2 Position;

	//
	Vector2 Size;
};

#endif


//font draw function
//INT DrawText(
//    LPD3DXSPRITE pSprite,
//    LPCTSTR pString,
//    int Count,
//    LPRECT pRect,
//    DWORD Format,
//    D3DCOLOR Color
//);