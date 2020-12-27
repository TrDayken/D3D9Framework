#include "ScenceManager.h"
#include "PlayScence.h"
#include "MapScence.h"


ScenceManager* ScenceManager::_instance = NULL;

void ScenceManager::AddScence(Scence* scence)
{
	currentscence = scence;
}

void ScenceManager::LoadScenceFromXML(const char* FilePath)
{
	TiXmlDocument TMXdoc(FilePath);

	if (TMXdoc.LoadFile())
	{
		TiXmlElement* root = TMXdoc.RootElement();

		for (TiXmlElement* XMLScence = root->FirstChildElement("Scence"); XMLScence != NULL ; XMLScence = XMLScence->NextSiblingElement("Scence"))
		{
			Scence* scence = NULL;
			std::string type = XMLScence->Attribute("type");

			if (type == "PlayScence");
				scence = new PlayScence();

			TiXmlElement* XMLMap = XMLScence->FirstChildElement("Map");

			for (TiXmlElement* XMLtexture = XMLMap->FirstChildElement("Texture"); XMLtexture != NULL; XMLtexture = XMLtexture->NextSiblingElement("Texture"))
			{
				int a = 0, r = 0, g = 0, b = 0;
				std::string texid;
				std::string path;

				//XMLtexture->QueryIntAttribute("textureid", &texid);
				path = XMLtexture->Attribute("path");
				texid = XMLtexture->Attribute("textureid");
				XMLtexture->QueryIntAttribute("a", &a);
				XMLtexture->QueryIntAttribute("r", &r);
				XMLtexture->QueryIntAttribute("g", &g);
				XMLtexture->QueryIntAttribute("b", &b);

				Textures::GetInstance()->AddTexture(texid, ToLPCWSTR(path), D3DCOLOR_ARGB(a, r, g, b));
			}

			for (TiXmlElement* XMLsprite = XMLMap->FirstChildElement("Sprite"); XMLsprite != NULL; XMLsprite = XMLsprite->NextSiblingElement("Sprite"))
			{
				//std::string textureid;
				std::string path = XMLsprite->Attribute("path");

				SpriteManager::GetInstance()->AddSpriteUsingXML(path.c_str());
			}

			for (TiXmlElement* XMLAnimation = XMLMap->FirstChildElement("Animation"); XMLAnimation != NULL; XMLAnimation = XMLAnimation->NextSiblingElement("Animation"))
			{
				std::string path = XMLAnimation->Attribute("path");

				AnimationManager::GetInstance()->AddAnimationUsingXML(path.c_str());
			}

			AddScence(scence);
		}

		DebugOut(L"[INFO] Load Scence successful \n");
	}
	else
	{
		DebugOut(L"[ERROR] failed to load Scence \n");
	}
}

Scence* ScenceManager::getCurrentScence()
{
	return currentscence;
}

ScenceManager* ScenceManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new ScenceManager();
	return _instance;
}
