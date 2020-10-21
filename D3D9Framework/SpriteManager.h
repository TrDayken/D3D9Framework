#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Sprite.h"
#include "tinyXML/tinyxml/tinyxml.h"

class SpriteManager
{
private:
	static SpriteManager* __instance;

	std::unordered_map<std::string, LPSPRITE> sprites;

public:
	void AddSprite(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	void AddSprite1(std::string id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 texture);

	void AddSpriteUsingXML(const char* FilePath, LPDIRECT3DTEXTURE9 texture);

	LPSPRITE GetSprite(std::string id);

	static SpriteManager* GetInstance();
};

#endif