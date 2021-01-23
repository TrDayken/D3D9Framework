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
			std::string id, mappath, filepath;

			TiXmlElement* XMLmap = XMLScence->FirstChildElement("Map");

			id = XMLmap->Attribute("id");
			mappath = XMLmap->Attribute("filelocation");
			filepath = XMLmap->Attribute("filepath");

			Scence* scence = NULL;
			std::string type = XMLScence->Attribute("type");

			if (type == "PlayScence")
			{
				scence = new PlayScence(id, mappath, filepath);
				auto cast = dynamic_cast<PlayScence*>(scence);
				this->Pair(id, scence);

				TiXmlElement* XMLCamera = XMLScence->FirstChildElement("Camera");

				if (XMLCamera != NULL)
				{
					int jumpbound = 0;
					int boundl = 0, boundt = 0, boundr = 0, boundb = 0;

					XMLCamera->QueryIntAttribute("jumpbound", &jumpbound);

					XMLCamera->QueryIntAttribute("boundl", &boundl);
					XMLCamera->QueryIntAttribute("boundt", &boundt);
					XMLCamera->QueryIntAttribute("boundr", &boundr);
					XMLCamera->QueryIntAttribute("boundb", &boundb);

					cast->setStartBound(boundl, boundr, boundt, boundb);

					float startx, starty;
					bool isstatic, isfollow, scrollx, scrolly;

					XMLCamera->QueryFloatAttribute("startx", &startx);
					XMLCamera->QueryFloatAttribute("starty", &starty);

					XMLCamera->QueryBoolAttribute("static", &isstatic);
					XMLCamera->QueryBoolAttribute("follow", &isfollow);
					XMLCamera->QueryBoolAttribute("scrollx", &scrollx);
					XMLCamera->QueryBoolAttribute("scrolly", &scrolly);

					cast->setJumpBound(jumpbound);
					cast->setStartConfig(startx, starty, isstatic, isfollow, scrollx, scrolly);
				}
			}
			else if (type == "MapScence")
			{
				scence = new MapScence(id, mappath, filepath);
				this->Pair(id, scence);
				AddScence(scence);
			}


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

void ScenceManager::LoadSource(const char* FilePath)
{
	TiXmlDocument TMXdoc(FilePath);

	if (TMXdoc.LoadFile())
	{
		TiXmlElement* root = TMXdoc.RootElement();
		for (TiXmlElement* XMLsource = root->FirstChildElement("Source"); XMLsource != NULL; XMLsource = XMLsource->NextSiblingElement("Scence"))
		{
			for (TiXmlElement* XMLtexture = XMLsource->FirstChildElement("Texture"); XMLtexture != NULL; XMLtexture = XMLtexture->NextSiblingElement("Texture"))
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

			for (TiXmlElement* XMLsprite = XMLsource->FirstChildElement("Sprite"); XMLsprite != NULL; XMLsprite = XMLsprite->NextSiblingElement("Sprite"))
			{
				//std::string textureid;
				std::string path = XMLsprite->Attribute("path");

				SpriteManager::GetInstance()->AddSpriteUsingXML(path.c_str());
			}

			for (TiXmlElement* XMLAnimation = XMLsource->FirstChildElement("Animation"); XMLAnimation != NULL; XMLAnimation = XMLAnimation->NextSiblingElement("Animation"))
			{
				std::string path = XMLAnimation->Attribute("path");

				AnimationManager::GetInstance()->AddAnimationUsingXML(path.c_str());
			}
		}
	}
}

void ScenceManager::SwitchScence(std::string id)
{
	currentscence->Unload();

	currentscence = loadedScenes[id];
	currentscence->Load();
	Game::GetInstance()->SetKeyHandler(currentscence->GetKeyEventHandler());
}

void ScenceManager::Pair(std::string id, Scence* scence)
{
	this->loadedScenes[id] = scence;
}

void ScenceManager::Load()
{
	this->currentscence->Load();
}

void ScenceManager::Unload()
{
	this->currentscence->Unload();
}
