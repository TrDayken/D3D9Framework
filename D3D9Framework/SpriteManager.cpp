#include "SpriteManager.h"

SpriteManager* SpriteManager::__instance = nullptr;

void SpriteManager::AddSprite(std::wstring id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture)
{
	RECT rect;
	rect.top = top;
	rect.bottom = bottom;
	rect.left = left;
	rect.right = right;
	LPSPRITE sprite = new Sprite(id, rect, texture);
	sprites[id] = sprite;
}

void SpriteManager::AddSpriteUsingXML(const char* file, LPDIRECT3DTEXTURE9 texture)
{
	TiXmlDocument doc = TiXmlDocument(file);

	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{

	}
}

LPSPRITE SpriteManager::GetSprite(std::wstring id)
{
	return sprites[id];
}

SpriteManager* SpriteManager::GetInstance()
{
	if (__instance == NULL)
		__instance = new SpriteManager();
	return __instance;
}
