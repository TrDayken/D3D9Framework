#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Sprite.h"
#include "tinyXML/tinyxml/tinyxml.h"

class SpriteManager
{
private:
	static SpriteManager* __instance;

	std::unordered_map<std::wstring, LPSPRITE> sprites;

public:
	void AddSprite(std::wstring id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	
	void AddSpriteUsingXML(const char* file, LPDIRECT3DTEXTURE9 texture);

	LPSPRITE GetSprite(std::wstring id);

	static SpriteManager* GetInstance();
};


