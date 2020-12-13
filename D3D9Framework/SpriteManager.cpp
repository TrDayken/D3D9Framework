#include "SpriteManager.h"
#include "Textures.h"

SpriteManager* SpriteManager::__instance = nullptr;

void SpriteManager::AddSprite(std::string id, int left, int top, int right, int bottom,int xpivot, int ypivot, LPDIRECT3DTEXTURE9 texture)
{
	RECT rect;
	rect.top = top;
	rect.bottom = bottom;
	rect.left = left;
	rect.right = right;
	LPSPRITE sprite = new Sprite(id, rect,xpivot,ypivot, texture);
	sprites[id] = sprite;
}

void SpriteManager::AddSpriteX3(std::string id, int left, int top, int width, int height,int xpivot, int ypivot, LPDIRECT3DTEXTURE9 texture)
{
	RECT rect;
	rect.left = left*3;
	rect.top = top*3;
	rect.right = left*3 + width*3;
	rect.bottom = top*3 + height*3;
	LPSPRITE sprite = new Sprite(id, rect,xpivot, ypivot, texture);
	sprites[id] = sprite;
}


void SpriteManager::AddSpriteUsingXML(const char* FilePath)
{
	TiXmlDocument XMLdoc(FilePath);

	if (XMLdoc.LoadFile())
	{
		TiXmlElement* root = XMLdoc.RootElement();

		for (TiXmlElement* XMLtexture = root->FirstChildElement("Textures"); XMLtexture != NULL ; XMLtexture = XMLtexture->NextSiblingElement("Textures"))
		{
			std::string texture = XMLtexture->Attribute("textureId");
			for (TiXmlElement* XMLsprite = XMLtexture->FirstChildElement("Sprite"); XMLsprite != NULL; XMLsprite = XMLsprite->NextSiblingElement("Sprite"))
			{
				int left, top, width, height;
				int xpivot = 0;
				int ypivot = 0;
				std::string id = XMLsprite->Attribute("id");

				XMLsprite->QueryIntAttribute("left", &left);
				XMLsprite->QueryIntAttribute("top", &top);
				XMLsprite->QueryIntAttribute("height", &height);
				XMLsprite->QueryIntAttribute("width", &width);
				XMLsprite->QueryIntAttribute("xPivot", &xpivot);
				XMLsprite->QueryIntAttribute("yPivot", &ypivot);

				AddSpriteX3(id, left, top, width, height, xpivot, ypivot, Textures::GetInstance()->GetTexture(texture));

				//DebugOut(L"[INFO] loaded spirte:%s \n", id.c_str());

				OutputDebugStringW(ToLPCWSTR("[INFO] loaded spirte: " + id + "\n"));
			}
		}
	}
	else
	{
		DebugOut(L"[ERROR]could not load file: %s", FilePath);
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
