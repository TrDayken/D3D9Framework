#include "SpriteManager.h"

SpriteManager* SpriteManager::__instance = nullptr;

void SpriteManager::AddSprite(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture)
{
	RECT rect;
	rect.top = top;
	rect.bottom = bottom;
	rect.left = left;
	rect.right = right;
	LPSPRITE sprite = new Sprite(id, rect, texture);
	sprites[id] = sprite;
}

void SpriteManager::AddSprite1(std::string id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 texture)
{
	RECT rect;
	rect.top = top*3;
	rect.bottom = top*3 + height*3;
	rect.left = left*3;
	rect.right = left*3 + width*3;
	LPSPRITE sprite = new Sprite(id, rect, texture);
	sprites[id] = sprite;
}


void SpriteManager::AddSpriteUsingXML(const char* FilePath, LPDIRECT3DTEXTURE9 texture)
{
	TiXmlDocument XMLdoc(FilePath);

	if (XMLdoc.LoadFile())
	{
		TiXmlElement* root	= XMLdoc.RootElement()->FirstChildElement();

		TiXmlElement* XMLsprite = NULL;

		for (XMLsprite = root->FirstChildElement(); XMLsprite != NULL;XMLsprite = XMLsprite->NextSiblingElement())
		{
			int left, top, width, height;
			std::string id = XMLsprite->Attribute("id");
			XMLsprite->QueryIntAttribute("left",&left);
			XMLsprite->Attribute("top", &top);
			XMLsprite->Attribute("width", &width);
			XMLsprite->Attribute("height" , &height);
			AddSprite1(id, left, top ,width, height, texture);

			DebugOut(L"[INFO] loaded %x \n", id);
		}
	}
	else
	{
		DebugOut(L"[ERROR]could not load file: %n", FilePath);
	}
}

LPSPRITE SpriteManager::GetSprite(std::string id)
{
	return sprites[id];
}

SpriteManager* SpriteManager::GetInstance()
{
	if (__instance == NULL)
		__instance = new SpriteManager();
	return __instance;
}
