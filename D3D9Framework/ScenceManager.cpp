#include "ScenceManager.h"

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
				//scence = new PlayScence();

			TiXmlElement* XMLMap = XMLScence->FirstChildElement("Map");

			for (TiXmlElement* XMLtexture = XMLMap->FirstChildElement("Texture"); XMLtexture != NULL; XMLtexture = XMLtexture->NextSiblingElement("Texture"))
			{
				int texid = NULL;
				int a = 0, r = 0, g = 0, b = 0;
				std::string path;
				path = XMLtexture->Attribute("path");
				XMLtexture->QueryIntAttribute("textureid", &texid);
				XMLtexture->QueryIntAttribute("a", &a);
				XMLtexture->QueryIntAttribute("r", &r);
				XMLtexture->QueryIntAttribute("g", &g);
				XMLtexture->QueryIntAttribute("b", &b);

				Textures::GetInstance()->AddTexture(texid, ToLPCWSTR(path), D3DCOLOR_ARGB(a, r, g, b));
			}
		}

		DebugOut(L"[INFO] map Scence successful \n");
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
