#include "AnimationManager.h"

AnimationManager * AnimationManager::_instance = NULL;

void AnimationManager::AddAnimation(std::string id, LPANIMATION animation)
{
	animationDatabase[id] = animation;
}

LPANIMATION AnimationManager::GetAnimation(std::string id)
{
	LPANIMATION ani = animationDatabase[id];
	if (ani == NULL)
		OutputDebugStringW(ToLPCWSTR("[ERROR] Failed to find animation id: " + id + "\n"));
	return ani;
}

void AnimationManager::Clear()
{
	for (auto x : animationDatabase)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animationDatabase.clear();
}

void AnimationManager::AddAnimationUsingXML(const char* FilePath)
{
	TiXmlDocument XMLdoc(FilePath);

	if (XMLdoc.LoadFile())
	{
		TiXmlElement* root = XMLdoc.RootElement();

		for (TiXmlElement* XMLtexture = root->FirstChildElement("Textures"); XMLtexture != NULL; XMLtexture = XMLtexture->NextSiblingElement("Textures"))
		{
			for (TiXmlElement* XMLanimation = XMLtexture->FirstChildElement("Animation"); XMLanimation != NULL; XMLanimation = XMLanimation->NextSiblingElement("Animation"))
			{
				LPANIMATION ani;
				int aniframetime;

				std::string aniID = XMLanimation->Attribute("aniId");
				XMLanimation->QueryIntAttribute("frameTime", &aniframetime);
				ani = new Animation(aniframetime);

				for (TiXmlElement* XMLanimationsprites = XMLanimation->FirstChildElement("Sprite"); XMLanimationsprites != NULL; XMLanimationsprites = XMLanimationsprites->NextSiblingElement("Sprite"))
				{
					int frametime;
					std::string spriteId = XMLanimationsprites->Attribute("id");
					XMLanimationsprites->QueryIntAttribute("frameTime", &frametime);

					ani->AddFrame(spriteId, frametime);
				}

				AddAnimation(aniID, ani);

				//DebugOut(L"[INFO] created animation: %d \n", aniID);
				OutputDebugStringW(ToLPCWSTR("[INFO] created animation: " + aniID + "\n"));
			}
		}
	}
	else
	{
		DebugOut(L"[ERROR] could not load file %d \n", FilePath);
	}
}

AnimationManager* AnimationManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new AnimationManager();
	return _instance;
}
